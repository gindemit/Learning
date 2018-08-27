package com.gindemit.dictionary.activities;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Messenger;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.gindemit.dictionary.R;
import com.gindemit.dictionary.io.IObbFilesCheckerClient;
import com.gindemit.dictionary.io.ObbFilesUnpacker;
import com.gindemit.dictionary.services.ObbDownloadService;
import com.google.android.vending.expansion.downloader.DownloadProgressInfo;
import com.google.android.vending.expansion.downloader.DownloaderClientMarshaller;
import com.google.android.vending.expansion.downloader.DownloaderServiceMarshaller;
import com.google.android.vending.expansion.downloader.Helpers;
import com.google.android.vending.expansion.downloader.IDownloaderClient;
import com.google.android.vending.expansion.downloader.IDownloaderService;
import com.google.android.vending.expansion.downloader.IStub;

public class ObbDownloadAndUnpackActivity extends AppCompatActivity implements IDownloaderClient, IObbFilesCheckerClient {

    private static final String LOG_TAG = "LVLDownloader";
    private ProgressBar mProgressBar;

    private TextView mStatusText;
    private TextView mProgressFraction;
    private TextView mProgressPercent;
    private TextView mAverageSpeed;
    private TextView mTimeRemaining;

    private View mDashboard;
    private View mCellMessage;

    private Button mPauseButton;

    private boolean mStatePaused;

    private IDownloaderService mRemoteService;

    private IStub mDownloaderClientStub;

    private ObbFilesUnpacker mObbFilesUnpacker;

    private void updateStatusText(int newState) {
        mStatusText.setText(Helpers.getDownloaderStringResourceIDFromState(newState));
    }

    private void setButtonPausedState(boolean paused) {
        mStatePaused = paused;
        int stringResourceID = paused ? R.string.text_button_resume :
                R.string.text_button_pause;
        mPauseButton.setText(stringResourceID);
    }

    /**
     * Calculating a moving average for the validation speed so we don't get
     * jumpy calculations for time etc.
     */
    static private final float SMOOTHING_FACTOR = 0.005f;

    /**
     * If the download isn't present, we initialize the download UI. This ties
     * all of the controls into the remote service calls.
     */
    private void initializeDownloadUI() {
        mDownloaderClientStub = DownloaderClientMarshaller.CreateStub
                (this, ObbDownloadService.class);
        setContentView(R.layout.activity_obb_download_and_npack);

        mProgressBar = (ProgressBar) findViewById(R.id.progressBar);
        mStatusText = (TextView) findViewById(R.id.statusText);
        mProgressFraction = (TextView) findViewById(R.id.progressAsFraction);
        mProgressPercent = (TextView) findViewById(R.id.progressAsPercentage);
        mAverageSpeed = (TextView) findViewById(R.id.progressAverageSpeed);
        mTimeRemaining = (TextView) findViewById(R.id.progressTimeRemaining);
        mDashboard = findViewById(R.id.downloaderDashboard);
        mCellMessage = findViewById(R.id.approveCellular);
        mPauseButton = (Button) findViewById(R.id.pauseButton);
        Button wifiSettingsButton = (Button) findViewById(R.id.wifiSettingsButton);

        mPauseButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (mStatePaused) {
                    mRemoteService.requestContinueDownload();
                } else {
                    mRemoteService.requestPauseDownload();
                }
                setButtonPausedState(!mStatePaused);
            }
        });

        wifiSettingsButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
            }
        });

        Button resumeOnCell = (Button) findViewById(R.id.resumeOverCellular);
        resumeOnCell.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mRemoteService.setDownloadFlags(IDownloaderService.FLAGS_DOWNLOAD_OVER_CELLULAR);
                mRemoteService.requestContinueDownload();
                mCellMessage.setVisibility(View.GONE);
            }
        });

    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mObbFilesUnpacker = new ObbFilesUnpacker(this);
       initializeDownloadUI();

        if (ObbFilesUnpacker.expansionFilesNotDelivered(this)) {
            tryStartDownload();
        } else {
            mObbFilesUnpacker.unpackObbZipFiles();
        }

    }

    private void tryStartDownload() {
        try {
            Intent launchIntent = ObbDownloadAndUnpackActivity.this.getIntent();
            Intent intentToLaunchThisActivityFromNotification = new Intent(
                    ObbDownloadAndUnpackActivity
                            .this, ObbDownloadAndUnpackActivity.this.getClass());
            intentToLaunchThisActivityFromNotification.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK |
                    Intent.FLAG_ACTIVITY_CLEAR_TOP);
            intentToLaunchThisActivityFromNotification.setAction(launchIntent.getAction());

            if (launchIntent.getCategories() != null) {
                for (String category : launchIntent.getCategories()) {
                    intentToLaunchThisActivityFromNotification.addCategory(category);
                }
            }

            // Build PendingIntent used to open this activity from
            // Notification
            PendingIntent pendingIntent = PendingIntent.getActivity(
                    ObbDownloadAndUnpackActivity.this,
                    0, intentToLaunchThisActivityFromNotification,
                    PendingIntent.FLAG_UPDATE_CURRENT);
            // Request to start the download
            int startResult = DownloaderClientMarshaller.startDownloadServiceIfRequired(this,
                    pendingIntent, ObbDownloadService.class);

            if (startResult != DownloaderClientMarshaller.NO_DOWNLOAD_REQUIRED) {
                // The DownloaderService has started downloading the files,
                // show progress
                initializeDownloadUI();
            } // otherwise, download not needed so we fall through to
            // starting the movie
        } catch (PackageManager.NameNotFoundException e) {
            Log.e(LOG_TAG, "Cannot find own package! MAYDAY!");
            e.printStackTrace();
        }
    }

    @Override
    protected void onStart() {
        if (null != mDownloaderClientStub) {
            mDownloaderClientStub.connect(this);
        }
        super.onStart();
    }

    @Override
    protected void onStop() {
        if (null != mDownloaderClientStub) {
            mDownloaderClientStub.disconnect(this);
        }
        super.onStop();
    }

    /**
     * Critical implementation detail. In onServiceConnected we create the
     * remote service and marshaler. This is how we pass the client information
     * back to the service so the client can be properly notified of changes. We
     * must do this every time we reconnect to the service.
     */
    @Override
    public void onServiceConnected(Messenger m) {
        mRemoteService = DownloaderServiceMarshaller.CreateProxy(m);
        mRemoteService.onClientUpdated(mDownloaderClientStub.getMessenger());
    }

    /**
     * The download state should trigger changes in the UI --- it may be useful
     * to show the state as being indeterminate at times. This sample can be
     * considered a guideline.
     */
    @Override
    public void onDownloadStateChanged(int newState) {
        boolean showDashboard = true;
        boolean showCellMessage = false;
        boolean paused;
        boolean indeterminate;
        switch (newState) {
            case IDownloaderClient.STATE_IDLE:
                // STATE_IDLE means the service is listening, so it's
                // safe to start making calls via mRemoteService.
                paused = false;
                indeterminate = true;
                break;
            case IDownloaderClient.STATE_CONNECTING:
            case IDownloaderClient.STATE_FETCHING_URL:
                showDashboard = true;
                paused = false;
                indeterminate = true;
                break;
            case IDownloaderClient.STATE_DOWNLOADING:
                paused = false;
                showDashboard = true;
                indeterminate = false;
                break;

            case IDownloaderClient.STATE_FAILED_CANCELED:
            case IDownloaderClient.STATE_FAILED:
            case IDownloaderClient.STATE_FAILED_FETCHING_URL:
            case IDownloaderClient.STATE_FAILED_UNLICENSED:
                paused = true;
                showDashboard = false;
                indeterminate = false;
                break;
            case IDownloaderClient.STATE_PAUSED_NEED_CELLULAR_PERMISSION:
            case IDownloaderClient.STATE_PAUSED_WIFI_DISABLED_NEED_CELLULAR_PERMISSION:
                showDashboard = false;
                paused = true;
                indeterminate = false;
                showCellMessage = true;
                break;

            case IDownloaderClient.STATE_PAUSED_BY_REQUEST:
                paused = true;
                indeterminate = false;
                break;
            case IDownloaderClient.STATE_PAUSED_ROAMING:
            case IDownloaderClient.STATE_PAUSED_SDCARD_UNAVAILABLE:
                paused = true;
                indeterminate = false;
                break;
            case IDownloaderClient.STATE_COMPLETED:
                showDashboard = false;
                paused = false;
                indeterminate = false;
                mObbFilesUnpacker.unpackObbZipFiles();
                return;
            default:
                paused = true;
                indeterminate = true;
                showDashboard = true;
        }
        int newDashboardVisibility = showDashboard ? View.VISIBLE : View.GONE;
        if (mDashboard.getVisibility() != newDashboardVisibility) {
            mDashboard.setVisibility(newDashboardVisibility);
        }
        int cellMessageVisibility = showCellMessage ? View.VISIBLE : View.GONE;
        if (mCellMessage.getVisibility() != cellMessageVisibility) {
            mCellMessage.setVisibility(cellMessageVisibility);
        }

        mProgressBar.setIndeterminate(indeterminate);
        setButtonPausedState(paused);
        updateStatusText(newState);
    }

    /**
     * Sets the state of the various controls based on the progressinfo object
     * sent from the downloader service.
     */
    @Override
    public void onDownloadProgress(DownloadProgressInfo progress) {
        mAverageSpeed.setText(getString(R.string.kilobytes_per_second,
                Helpers.getSpeedString(progress.mCurrentSpeed)));
        mTimeRemaining.setText(getString(R.string.time_remaining,
                Helpers.getTimeRemaining(progress.mTimeRemaining)));

        progress.mOverallTotal = progress.mOverallTotal;
        mProgressBar.setMax((int) (progress.mOverallTotal >> 8));
        mProgressBar.setProgress((int) (progress.mOverallProgress >> 8));
        mProgressPercent.setText(Long.toString(progress.mOverallProgress
                * 100 /
                progress.mOverallTotal) + "%");
        mProgressFraction.setText(Helpers.getDownloadProgressString
                (progress.mOverallProgress,
                        progress.mOverallTotal));
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    // ObbFilesUnpacker client methods
    @Override
    public Context getContext() {
        return this;
    }
    @Override
    public void onPreCheck() {
        mDashboard.setVisibility(View.VISIBLE);
        mCellMessage.setVisibility(View.GONE);
        mStatusText.setText(R.string.text_unpacking_database_file);
        mPauseButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mObbFilesUnpacker.CancelUnpacking();
            }
        });
        mPauseButton.setText(R.string.text_button_cancel_unpacking);
    }

    @Override
    public void onCheckProgress(DownloadProgressInfo progress) {
        onDownloadProgress(progress);
    }

    @Override
    public void onPostCheck(boolean result) {
        if (result) {
            mDashboard.setVisibility(View.VISIBLE);
            mCellMessage.setVisibility(View.GONE);
            mStatusText.setText(R.string.text_unpacking_complete);
            mPauseButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    finish();
                }
            });
            mPauseButton.setText(android.R.string.ok);
        } else {
            mDashboard.setVisibility(View.VISIBLE);
            mCellMessage.setVisibility(View.GONE);
            mStatusText.setText(R.string.text_unpacking_failed);
            mPauseButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent intent = getIntent();
                    finish();
                    startActivity(intent);
                }
            });
            mPauseButton.setText(R.string.text_button_try_again);
        }
    }
}

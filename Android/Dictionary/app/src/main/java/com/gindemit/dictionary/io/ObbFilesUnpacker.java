package com.gindemit.dictionary.io;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.AsyncTask;
import android.os.SystemClock;
import android.os.storage.OnObbStateChangeListener;
import android.os.storage.StorageManager;
import android.util.Log;

import com.google.android.vending.expansion.downloader.DownloadProgressInfo;
import com.google.android.vending.expansion.downloader.Helpers;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import static android.content.Context.STORAGE_SERVICE;

public class ObbFilesUnpacker {
    private static final float SMOOTHING_FACTOR = 0.005f;
    private static final String PACKED_OBB_FILE_NAME = "ru_de_dict.zip";
    private static final String UNPACKED_OBB_FILE_NAME = "ru_de_dict.db";

    private final IObbFilesCheckerClient mClient;
    private boolean mCancelUnpacking;

    public ObbFilesUnpacker(IObbFilesCheckerClient client) {
        mClient = client;
    }

    private static class AsynkTaskData {
        final StorageManager StorageManager;
        final String OutputDirPath;
        final String ObbFilePath;

        AsynkTaskData(StorageManager storageManager, String outputDirPath, String obbFilePath) {
            StorageManager = storageManager;
            OutputDirPath = outputDirPath;
            ObbFilePath = obbFilePath;
        }
    }

    private static class ObbFile {
        final boolean IsMain;
        final int FileVersion;
        final long FileSize;

        ObbFile(boolean isMain, int fileVersion, long fileSize) {
            IsMain = isMain;
            FileVersion = fileVersion;
            FileSize = fileSize;
        }
    }

    private static final ObbFile[] obbFiles = {
            new ObbFile(
                    true,
                    1,
                    66043959L
            )
    };

    public static boolean expansionFilesNotDelivered(Context context) {
        for (ObbFile obbFile : obbFiles) {
            String fileName = Helpers.getExpansionAPKFileName(context, obbFile.IsMain, obbFile.FileVersion);
            if (!Helpers.doesFileExist(context, fileName, obbFile.FileSize, false)) {
                return true;
            }
        }
        return false;
    }

    public void unpackObbZipFiles() {
        for (ObbFile obbFile : obbFiles) {
            String obbFileName = Helpers.getExpansionAPKFileName(
                    mClient.getContext(),
                    obbFile.IsMain,
                    obbFile.FileVersion);
            if (!Helpers.doesFileExist(
                    mClient.getContext(),
                    obbFileName,
                    obbFile.FileSize,
                    false)) {
                mClient.onPostCheck(false);
                return;
            }
            final String outputDirPath = mClient.getContext().getExternalFilesDir("database").getAbsolutePath();
            final String obbFileAbsolutePath = Helpers.generateObbFileAbsolutePath(mClient.getContext(), obbFileName);
            final StorageManager storageManager = (StorageManager) mClient.getContext().getSystemService(STORAGE_SERVICE);
            final ObbFilesUnpacker self = this;

            OnObbStateChangeListener obbStateChangeListener = new OnObbStateChangeListener() {
                public void onObbStateChange(String path, int state) {
                    self.onObbStateChange(path, state, storageManager, outputDirPath);
                }
            };
            storageManager.mountObb(obbFileAbsolutePath, "1qazxsw2", obbStateChangeListener);
        }
    }

    private void onObbStateChange(final String obbPath, int state, final StorageManager storageManager, String outputDirPath) {
        if (state == OnObbStateChangeListener.ERROR_COULD_NOT_MOUNT ||
                state == OnObbStateChangeListener.ERROR_INTERNAL ||
                state == OnObbStateChangeListener.ERROR_PERMISSION_DENIED ) {
            mClient.onPostCheck(false);
            return;
        }
        if (state == OnObbStateChangeListener.ERROR_ALREADY_MOUNTED) {
            storageManager.unmountObb(obbPath, false, new OnObbStateChangeListener() {
                @Override
                public void onObbStateChange(String path, int state) {
                    super.onObbStateChange(path, state);
                }
            });
            mClient.onPostCheck(false);
            return;
        }
        if (!storageManager.isObbMounted(obbPath)) {
            mClient.onPostCheck(false);
            return;
        }

        @SuppressLint("StaticFieldLeak") AsyncTask<Object, DownloadProgressInfo, Boolean> validationTask = new AsyncTask<Object, DownloadProgressInfo, Boolean>() {

            @Override
            protected void onPreExecute() {
                mClient.onPreCheck();
                super.onPreExecute();
            }

            @Override
            protected Boolean doInBackground(Object... params) {
                AsynkTaskData asynkTaskData = (AsynkTaskData) params[0];
                String newPath = asynkTaskData.StorageManager.getMountedObbPath(asynkTaskData.ObbFilePath);
                File expPath = new File(newPath, PACKED_OBB_FILE_NAME);

                try {
                    InputStream is = new FileInputStream(expPath);
                    ZipInputStream zis = new ZipInputStream(new BufferedInputStream(is));

                    ZipEntry ze;
                    byte[] buffer = new byte[1024 * 1024];
                    int count;

                    while ((ze = zis.getNextEntry()) != null) {
                        String filename = ze.getName();

                        long totalCompressedLength = ze.getSize();
                        float averageVerifySpeed = 0;
                        long totalBytesRemaining = totalCompressedLength;
                        long timeRemaining;

                        if (ze.isDirectory()) {
                            File fmd = new File(asynkTaskData.OutputDirPath, filename);
                            fmd.mkdirs();
                            continue;
                        }

                        long startTime = SystemClock.uptimeMillis();
                        FileOutputStream fout = new FileOutputStream(new File(asynkTaskData.OutputDirPath, filename));
                        while ((count = zis.read(buffer)) != -1) {
                            fout.write(buffer, 0, count);

                            long currentTime = SystemClock.uptimeMillis();
                            long timePassed = currentTime - startTime;
                            totalBytesRemaining -= count;
                            if (timePassed > 0) {
                                float currentSpeedSample = (float)count / (float)timePassed;
                                if (0 != averageVerifySpeed) {
                                    averageVerifySpeed = SMOOTHING_FACTOR
                                            * currentSpeedSample
                                            + (1 - SMOOTHING_FACTOR)
                                            * averageVerifySpeed;
                                } else {
                                    averageVerifySpeed = currentSpeedSample;
                                }
                                timeRemaining = (long) (totalBytesRemaining / averageVerifySpeed);
                                this.publishProgress(
                                        new DownloadProgressInfo(
                                                totalCompressedLength,
                                                totalCompressedLength - totalBytesRemaining,
                                                timeRemaining,
                                                averageVerifySpeed));
                            }
                            startTime = currentTime;
                            if (mCancelUnpacking)
                                return false;
                        }

                        fout.close();
                        zis.closeEntry();

                        this.publishProgress(
                                new DownloadProgressInfo(
                                        totalCompressedLength,
                                        totalCompressedLength - totalBytesRemaining,
                                        0,
                                        averageVerifySpeed));
                    }
                    zis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                    return false;
                }
                return true;
            }

            @Override
            protected void onProgressUpdate(DownloadProgressInfo... values) {
                mClient.onCheckProgress(values[0]);
                super.onProgressUpdate(values);
            }

            @Override
            protected void onPostExecute(Boolean result) {
                storageManager.unmountObb(obbPath, false, new OnObbStateChangeListener() {
                    @Override
                    public void onObbStateChange(String path, int state) {
                        super.onObbStateChange(path, state);
                    }
                });
                mClient.onPostCheck(result);
                super.onPostExecute(result);
            }

        };
        validationTask.execute(new AsynkTaskData(storageManager, outputDirPath, obbPath));
    }

    public static boolean unpackIsNecessary(Context context) {
        File unpackedDatabaseFilePath = context.getExternalFilesDir("database");
        File file = new File(unpackedDatabaseFilePath, UNPACKED_OBB_FILE_NAME);
        try {
            InputStream is = new FileInputStream(file);
            is.read();
            return false;
        } catch (IOException e) {
            Log.w("ExternalStorage", "Error writing " + file, e);
            return true;
        }
    }

    public void CancelUnpacking() {
        this.mCancelUnpacking = true;
    }
}

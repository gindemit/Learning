package com.gindemit.dictionary.activities;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.design.widget.TabLayout;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import com.gindemit.dictionary.R;
import com.gindemit.dictionary.fragments.IOnListFragmentInteractionListener;
import com.gindemit.dictionary.helpers.DialogViewer;
import com.gindemit.dictionary.helpers.PermissionRequestCode;
import com.gindemit.dictionary.helpers.PermissionsHelper;
import com.gindemit.dictionary.io.ExternalStoragePermissionChecker;
import com.gindemit.dictionary.io.IObbFilesCheckerClient;
import com.gindemit.dictionary.io.ObbFilesChecker;
import com.gindemit.dictionary.io.ObbFilesUnpacker;
import com.gindemit.dictionary.listeners.OnNavigationItemSelectedListener;
import com.gindemit.dictionary.listeners.OnPageChangedListener;
import com.gindemit.dictionary.pager_adapter.IMainPagerAdapterClient;
import com.gindemit.dictionary.pager_adapter.MainPagerAdapter;
import com.google.android.vending.expansion.downloader.DownloadProgressInfo;
import com.google.android.vending.expansion.downloader.Helpers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class MainActivity
        extends AppCompatActivity
        implements IOnListFragmentInteractionListener,
        IMainPagerAdapterClient {

    private ObbFilesChecker mObbFilesChecker;
    private ObbFilesUnpacker mObbFilesUnpacker;
    private NavigationView mNavigationView;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setupActionBar();
        mNavigationView = findViewById(R.id.navigation_view);

        ViewPager viewPager = findViewById(R.id.view_pager);
        PagerAdapter pagerAdapter = new MainPagerAdapter(getSupportFragmentManager(), this);
        viewPager.setAdapter(pagerAdapter);
        viewPager.addOnPageChangeListener(new OnPageChangedListener(mNavigationView));

        TabLayout tabLayout = findViewById(R.id.tabs);
        tabLayout.setupWithViewPager(viewPager);

        mNavigationView.setNavigationItemSelectedListener(
                new OnNavigationItemSelectedListener(tabLayout,
                    (DrawerLayout)findViewById(R.id.drawer_layout)));

        //onCreateLogic();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.app_bar_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.search_whole_word:
                item.setChecked(!item.isChecked());
                return true;
            case R.id.search_case_sensitive:
                item.setChecked(!item.isChecked());
                return true;
            case R.id.search_the_end:
                item.setChecked(!item.isChecked());
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void onCreateLogic() {
        if (!ExternalStoragePermissionChecker.canWriteToObbDir(this)) {
            RequestWriteExternalStoragePermission();
            return;
        }

        if (startDownloadObbActivityIfNecessary()) {
            return;
        }
        if (Helpers.externalMediaIsNotMounted()) {
            showMountExternalStorageMessage();
            return;
        }
        if (unzipObbIfNecessary()) {
            return;
        }

        // TODO: the db is unpacked and ready to use
        // Example of a call to a native method
        stringFromJNI();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[],
                                           int[] grantResults) {
        HandleWriteExternalStoragePermission(requestCode, grantResults);
    }

    private void HandleWriteExternalStoragePermission(int requestCode, int[] grantResults) {
        if (requestCode == PermissionRequestCode.WRITE_EXTERNAL_STORAGE_REQUEST_CODE.ordinal()) {
            // If request is cancelled, the result arrays are empty.
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                onCreateLogic(); // Go from start
            } else {
                DialogViewer.showAlertDialog(
                        this,
                        "Warning",
                        "No permission - no dictionary",
                        "Ask permission again",
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                RequestWriteExternalStoragePermission();
                            }
                        });
            }
        }
    }

    private boolean unzipObbIfNecessary() {
        mObbFilesUnpacker = new ObbFilesUnpacker();
        if (mObbFilesUnpacker.UnpackIsNecessary()) {
            Intent startObbUnpackActivityIntent = new Intent(MainActivity.this, ObbDownloaderActivity.class);
            MainActivity.this.startActivity(startObbUnpackActivityIntent);
            return true;
        }
        return false;
    }

    private void showMountExternalStorageMessage() {

    }

    private boolean startDownloadObbActivityIfNecessary() {
        if (ObbFilesChecker.expansionFilesNotDelivered(this)) {
            Intent startObbDownloaderActivityIntent = new Intent(MainActivity.this, ObbDownloaderActivity.class);
            MainActivity.this.startActivity(startObbDownloaderActivityIntent);
            return true;
        }
        return false;
    }

    private void RequestWriteExternalStoragePermission() {
        PermissionsHelper.RequestPermissionIfNeeded(
                this,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                PermissionRequestCode.WRITE_EXTERNAL_STORAGE_REQUEST_CODE);
    }

    private void setupActionBar() {
        Toolbar toolbar = findViewById(R.id.toolbar_main);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        /*final ActionBar actionBar = getSupportActionBar();
        actionBar.setDisplayShowHomeEnabled(true);
        actionBar.setDisplayHomeAsUpEnabled(true);
        actionBar.setHomeButtonEnabled(true);
        actionBar.setDisplayShowCustomEnabled(true);*/
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    @Override
    public Context getContext() {
        return this;
    }
}

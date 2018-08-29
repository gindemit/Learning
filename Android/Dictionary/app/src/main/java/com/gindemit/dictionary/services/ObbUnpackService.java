package com.gindemit.dictionary.services;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;

import com.gindemit.dictionary.io.IObbFilesUnpackerClient;
import com.gindemit.dictionary.io.ObbFilesUnpacker;
import com.google.android.vending.expansion.downloader.DownloadProgressInfo;

public class ObbUnpackService extends Service implements IObbFilesUnpackerClient {
    public class LocalBinder extends Binder {
        public ObbUnpackService getService() {
            return ObbUnpackService.this;
        }
    }

    private final IBinder mBinder = new LocalBinder();
    private ObbFilesUnpacker mObbFilesUnpacker;
    private IObbFilesUnpackerClient mClient;

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        mObbFilesUnpacker = new ObbFilesUnpacker(this);
    }

    public void cancelUnpacking() {
        mObbFilesUnpacker.cancelUnpacking();
    }

    public void setObbFilesUnpackerClient(IObbFilesUnpackerClient client) {
        mClient = client;
    }

    public void startUnpackingObbFiles() {
        mObbFilesUnpacker.unpackObbZipFiles();
    }

    //IObbFilesUnpackerClient
    @Override
    public Context getContext() {
        return this;
    }

    @Override
    public void onPreUnpack() {
        if (mClient != null)
            mClient.onPreUnpack();
    }

    @Override
    public void onUnpackProgress(DownloadProgressInfo progress) {
        if (mClient != null)
            mClient.onUnpackProgress(progress);
    }

    @Override
    public void onPostUnpack(boolean result) {
        if (mClient != null)
            mClient.onPostUnpack(result);
        if (result) {
            stopSelf();
        }
    }
}

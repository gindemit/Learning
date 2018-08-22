package com.gindemit.dictionary.broadcast_receivers;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import com.gindemit.dictionary.services.ObbDownloadService;

import com.google.android.vending.expansion.downloader.DownloaderClientMarshaller;

public class ObbAlarmReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        try {
            DownloaderClientMarshaller.startDownloadServiceIfRequired(context, intent, ObbDownloadService.class);
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
    }
}

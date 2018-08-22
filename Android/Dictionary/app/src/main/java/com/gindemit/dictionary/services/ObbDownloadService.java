package com.gindemit.dictionary.services;

import com.gindemit.dictionary.broadcast_receivers.ObbAlarmReceiver;
import com.google.android.vending.expansion.downloader.impl.DownloaderService;

public class ObbDownloadService extends DownloaderService {
    // stuff for LVL -- MODIFY FOR YOUR APPLICATION!
    private static final String BASE64_PUBLIC_KEY = "REPLACE THIS WITH YOUR PUBLIC KEY";
    // used by the preference obfuscater
    private static final byte[] SALT = new byte[] {
            1, 47, -12, -1, 54, 94,
            -108, -18, 49, 4, -6, -7, 7, 8, -107, -101, -34, 46, -3, 87
    };

    @Override
    public String getPublicKey() {
        return BASE64_PUBLIC_KEY;
    }

    @Override
    public byte[] getSALT() {
        return SALT;
    }

    @Override
    public String getAlarmReceiverClassName() {
        return ObbAlarmReceiver.class.getName();
    }
}

package com.gindemit.dictionary.services;

import com.gindemit.dictionary.broadcast_receivers.ObbAlarmReceiver;
import com.google.android.vending.expansion.downloader.impl.DownloaderService;

public class ObbDownloadService extends DownloaderService {
    // stuff for LVL -- MODIFY FOR YOUR APPLICATION!
    private static final String BASE64_PUBLIC_KEY =
            "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAlGnP71JlCSoNlbnpakT0k" +
                    "S8/MBC5N5cXAoojrjfP+bGmSiosQGld+t9IrSRQd6NyhaIJl96fqBliLI" +
                    "L2hBcHHsrCoLJ3dUwY7VekwBYKnLdMN0iAG+YP7UUatAA+BCeYRZEWwMX" +
                    "MJlBtspqJJ3X5MVtuMRm/wIncGXy0Wc3Nh154L25HYx4dBgtjJmJIdhVa" +
                    "HOmb2uLBot4II91bElN4cGB0KKlE2o8a1fhbk3+41TINzoudKigTcVjic" +
                    "IMN3qeA+ZXVkZJyROPpaaW+DpJLNOwTsN/jNx8vsllO+3cmDl8hQOHZiJ" +
                    "KPdYK5mN4plKVX3vSRlLkexIvJ11QlqRdxuwIDAQAB";
    // used by the preference obfuscater
    private static final byte[] SALT = new byte[] {
            1, 47, -12, -1, 54, 94,
            -108, -18, 49, 4, -6, -7, 7, 8, -112, -101, -34, 46, -3, 87
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

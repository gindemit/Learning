package com.gindemit.dictionary.io;

import android.content.Context;
import com.google.android.vending.expansion.downloader.DownloadProgressInfo;

public interface IObbFilesCheckerClient {
    Context GetContext();
    void onPreCheck();
    void onCheckProgress(DownloadProgressInfo progress);
    void onPostCheck(boolean result);
}

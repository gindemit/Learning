package com.gindemit.dictionary.io;

import android.content.Context;
import com.google.android.vending.expansion.downloader.DownloadProgressInfo;

public interface IObbFilesUnpackerClient {
    Context getContext();
    void onPreUnpack();
    void onUnpackProgress(DownloadProgressInfo progress);
    void onPostUnpack(boolean result);
}

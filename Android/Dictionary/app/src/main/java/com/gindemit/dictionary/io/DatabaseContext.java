package com.gindemit.dictionary.io;

import android.content.Context;
import android.content.ContextWrapper;
import android.database.DatabaseErrorHandler;
import android.database.sqlite.SQLiteDatabase;
import android.os.Environment;
import android.util.Log;

import java.io.File;

public class DatabaseContext extends ContextWrapper {
    private static final String LOG_TAG = "DatabaseContext";

    public DatabaseContext(Context base) {
        super(base);
    }

    @Override
    public File getDatabasePath(String name)  {
        File pathToDBDir = getExternalFilesDir(ObbFilesUnpacker.UNPACKED_OBB_FILE_DIR_NAME);
        String dbAbsolutePath = new File(pathToDBDir, name).getAbsolutePath();
        if (!dbAbsolutePath.endsWith(".db")) {
            dbAbsolutePath += ".db" ;
        }

        File result = new File(dbAbsolutePath);

        if (!result.getParentFile().exists()) {
            result.getParentFile().mkdirs();
        }

        if (Log.isLoggable(LOG_TAG, Log.WARN)) {
            Log.w(LOG_TAG, "getDatabasePath(" + name + ") = " + result.getAbsolutePath());
        }

        return result;
    }
    /* this version is called for android devices >= api-11. thank to @damccull for fixing this. */
    @Override
    public SQLiteDatabase openOrCreateDatabase(String name, int mode, SQLiteDatabase.CursorFactory factory, DatabaseErrorHandler errorHandler) {
        return openOrCreateDatabase(name,mode, factory);
    }

    /* this version is called for android devices < api-11 */
    @Override
    public SQLiteDatabase openOrCreateDatabase(String name, int mode, SQLiteDatabase.CursorFactory factory) {
        SQLiteDatabase result = SQLiteDatabase.openOrCreateDatabase(getDatabasePath(name), null);
        // SQLiteDatabase result = super.openOrCreateDatabase(name, mode, factory);
        if (Log.isLoggable(LOG_TAG, Log.WARN)) {
            Log.w(LOG_TAG, "openOrCreateDatabase(" + name + ",,) = " + result.getPath());
        }
        return result;
    }
}

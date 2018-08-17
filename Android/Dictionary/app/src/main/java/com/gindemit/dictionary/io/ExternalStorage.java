package com.gindemit.dictionary.io;

import android.content.Context;
import android.util.Log;

import com.gindemit.dictionary.R;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class ExternalStorage {

    private final Context _context;
    public ExternalStorage(Context context)
    {
        _context = context;
    }

    void createExternalStoragePrivateFile() {
        // Create a path where we will place our private file on external
        // storage.
        File file = new File(_context.getExternalFilesDir(null), "DemoFile.jpg");

        try {
            // Very simple code to copy a picture from the application's
            // resource into the external file.  Note that this code does
            // no error checking, and assumes the picture is small (does not
            // try to copy it in chunks).  Note that if external storage is
            // not currently mounted this will silently fail.
            InputStream is = _context.getResources().openRawResource(R.raw.ic_dictionary);
            OutputStream os = new FileOutputStream(file);
            byte[] data = new byte[is.available()];
            is.read(data);
            os.write(data);
            is.close();
            os.close();
        } catch (IOException e) {
            // Unable to create file, likely because external storage is
            // not currently mounted.
            Log.w("ExternalStorage", "Error writing " + file, e);
        }
    }

    void deleteExternalStoragePrivateFile() {
        // Get path for the file on external storage.  If external
        // storage is not currently mounted this will fail.
        File file = new File(_context.getExternalFilesDir(null), "DemoFile.jpg");
        if (file != null) {
            file.delete();
        }
    }

    boolean hasExternalStoragePrivateFile() {
        // Get path for the file on external storage.  If external
        // storage is not currently mounted this will fail.
        File file = new File(_context.getExternalFilesDir(null), "DemoFile.jpg");
        if (file != null) {
            return file.exists();
        }
        return false;
    }

}

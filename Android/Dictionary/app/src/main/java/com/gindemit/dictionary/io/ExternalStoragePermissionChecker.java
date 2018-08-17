package com.gindemit.dictionary.io;

import android.content.Context;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ExternalStoragePermissionChecker {

    private final Context _context;

    public ExternalStoragePermissionChecker(Context context)
    {
        _context = context;
    }

    private void CheckIfTheReadExternalStoragePermissionIsRequired()
    {
        String obb_filename = _context.getObbDir().getName();
        File obb = new File(obb_filename);
        boolean open_failed = false;

        try {
            BufferedReader br = new BufferedReader(new FileReader(obb));
            open_failed = false;
            ReadObbFile(br);
        } catch (IOException e) {
            open_failed = true;
        }

        if (open_failed) {
            // request READ_EXTERNAL_STORAGE permission before reading OBB file
            ReadObbFileWithPermission();
        }
    }
    void ReadObbFile(BufferedReader br)
    {
        //Save to getExternalFilesDir
        //getExternalFilesDir(null);
    }
    void ReadObbFileWithPermission()
    {}
}

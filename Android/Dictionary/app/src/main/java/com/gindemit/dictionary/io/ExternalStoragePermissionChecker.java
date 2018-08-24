package com.gindemit.dictionary.io;

import android.content.Context;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ExternalStoragePermissionChecker {


    public static boolean canWriteToObbDir(Context context)
    {
        String obb_filename = context.getObbDir().getName();
        File obb = new File(obb_filename);

        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(obb));
        } catch (IOException e) {
            return true;
        }
        return false;
    }
}

package com.gindemit.dictionary.helpers;

import android.app.Activity;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;

import com.gindemit.dictionary.io.ExternalStoragePermissionChecker;

public class PermissionsHelper {

    public static boolean RequestPermissionIfNeeded(Activity activity, String permission, PermissionRequestCode requestCode) {
        if (ContextCompat.checkSelfPermission(activity, permission)
                != PackageManager.PERMISSION_GRANTED) {

            if (ActivityCompat.shouldShowRequestPermissionRationale(activity, permission)) {
                DialogViewer.showAlertDialog(activity,
                        "Allow permission",
                        "Get the permission!",
                        "Ok",
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                Log.i(ExternalStoragePermissionChecker.class.getName(), "On permission alert ok click");
                            }
                        });
            } else {
                ActivityCompat.requestPermissions(activity, new String[]{permission}, requestCode.ordinal());
            }
            return false;
        }
        return true;
    }
}

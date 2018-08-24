package com.gindemit.dictionary.helpers;

import android.content.Context;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;

public class DialogViewer {

    public static void showAlertDialog(Context context,
                                       String title,
                                       String message,
                                       String pasitiveButtonText,
                                       final DialogInterface.OnClickListener listener) {
        new AlertDialog.Builder(context).
                setTitle(title).
                setMessage(message).
                setPositiveButton(pasitiveButtonText, listener);
    }
}

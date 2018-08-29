package com.gindemit.dictionary.io;


import android.content.Context;
import android.database.sqlite.SQLiteDatabase;

public class SQLiteOpenHelper extends android.database.sqlite.SQLiteOpenHelper {
    private static final int DATABASE_VERSION = 1;

    public SQLiteOpenHelper(Context context, String name) {
        super(new DatabaseContext(context), name, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {

    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {

    }
}

package com.gindemit.dictionary.activities;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.gindemit.dictionary.R;

public class SplashScreenActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash_screen);

        try {
            String version = getApplicationContext().getPackageManager().getPackageInfo(getApplicationContext().getPackageName(), 0).versionName;
            ((TextView) findViewById(R.id.txtVersion)).setText("Version: " + version);
            new Handler().postDelayed(new Runnable() {
                public void run() {
                    Intent localIntent = new Intent(SplashScreenActivity.this, MainActivity.class);
                    SplashScreenActivity.this.startActivity(localIntent);
                    SplashScreenActivity.this.finish();
                }
            }, 250L);
        }
        catch (PackageManager.NameNotFoundException paramBundle)
        {
            paramBundle.printStackTrace();
        }
    }
}

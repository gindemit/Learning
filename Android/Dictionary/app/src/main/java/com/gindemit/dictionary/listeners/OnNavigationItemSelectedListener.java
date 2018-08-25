package com.gindemit.dictionary.listeners;

import android.app.Activity;
import android.content.Context;
import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.design.widget.TabLayout;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.view.MenuItem;

import com.gindemit.dictionary.R;

public class OnNavigationItemSelectedListener implements NavigationView.OnNavigationItemSelectedListener {
    private final TabLayout mTabLayout;
    private final DrawerLayout mDrawerLayout;

    public OnNavigationItemSelectedListener(TabLayout tabLayout, DrawerLayout drawerLayout) {
        mTabLayout = tabLayout;
        mDrawerLayout = drawerLayout;
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {

        switch (item.getItemId()) {
            case R.id.navigation_home:
                mTabLayout.getTabAt(0).select();
                break;
            case R.id.navigation_history:
                mTabLayout.getTabAt(1).select();
                break;
            case R.id.navigation_bookmark:
                mTabLayout.getTabAt(2).select();
                break;
        }
        mDrawerLayout.closeDrawer(GravityCompat.START);
        return true;
    }
}

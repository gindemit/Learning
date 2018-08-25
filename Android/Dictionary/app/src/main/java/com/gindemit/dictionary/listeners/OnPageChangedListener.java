package com.gindemit.dictionary.listeners;

import android.support.design.widget.NavigationView;

import com.gindemit.dictionary.R;

public class OnPageChangedListener implements android.support.v4.view.ViewPager.OnPageChangeListener {

    private final NavigationView mNavigationView;
    public OnPageChangedListener(NavigationView navigationView) {
        mNavigationView = navigationView;
    }

    @Override
    public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

    }

    @Override
    public void onPageSelected(int position) {
        mNavigationView.getMenu().getItem(position).setChecked(true);
    }

    @Override
    public void onPageScrollStateChanged(int state) {

    }
}

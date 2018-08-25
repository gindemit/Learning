package com.gindemit.dictionary.pager_adapter;

import android.content.Context;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import com.gindemit.dictionary.R;
import com.gindemit.dictionary.fragments.bookmark.BookmarkPageFragment;
import com.gindemit.dictionary.fragments.history.HistoryPageFragment;
import com.gindemit.dictionary.fragments.search.SearchPageFragment;

public class MainPagerAdapter extends FragmentPagerAdapter {
    private final IMainPagerAdapterClient mClient;

    public MainPagerAdapter(FragmentManager fm, IMainPagerAdapterClient client) {
        super(fm);
        mClient = client;
    }

    @Override
    public Fragment getItem(int position) {
        switch (position) {
            case 0:
                return new SearchPageFragment();
            case 1:
                return new HistoryPageFragment();
            case 2:
                return new BookmarkPageFragment();
            default:
                return null;
        }
    }

    @Override
    public CharSequence getPageTitle(int position) {
        switch (position) {
            case 0:
                return mClient.getContext().getString(R.string.search_tab);
            case 1:
                return mClient.getContext().getString(R.string.history_tab);
            case 2:
                return mClient.getContext().getString(R.string.bookmark_tab);
            default:
                return null;
        }
    }

    @Override
    public int getCount() {
        return 3;
    }
}

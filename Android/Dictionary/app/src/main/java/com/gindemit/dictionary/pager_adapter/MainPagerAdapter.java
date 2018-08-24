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
    private final Context mContext;

    public MainPagerAdapter(FragmentManager fm, Context context) {
        super(fm);
        mContext = context;
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
            case 3:
                return new SearchPageFragment();
            case 4:
                return new HistoryPageFragment();
            case 5:
                return new BookmarkPageFragment();
            default:
                return null;
        }
    }

    @Override
    public CharSequence getPageTitle(int position) {
        switch (position) {
            case 0:
                return mContext.getString(R.string.search_tab);
            case 1:
                return mContext.getString(R.string.history_tab);
            case 2:
                return mContext.getString(R.string.bookmark_tab);
            case 3:
                return mContext.getString(R.string.search_tab);
            case 4:
                return mContext.getString(R.string.history_tab);
            case 5:
                return mContext.getString(R.string.bookmark_tab);
            default:
                return null;
        }
    }

    @Override
    public int getCount() {
        return 6;
    }
}

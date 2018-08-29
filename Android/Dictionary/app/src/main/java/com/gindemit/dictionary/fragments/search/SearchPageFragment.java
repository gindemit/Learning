package com.gindemit.dictionary.fragments.search;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.gindemit.dictionary.R;
import com.gindemit.dictionary.fragments.IOnListFragmentInteractionListener;
import com.gindemit.dictionary.io.SQLiteOpenHelper;

public class SearchPageFragment extends Fragment {

    private IOnListFragmentInteractionListener mListener;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_searchitem_list, container, false);

        // Set the adapter
        if (view instanceof RecyclerView) {
            Context context = view.getContext();
            RecyclerView recyclerView = (RecyclerView) view;
            recyclerView.setLayoutManager(new LinearLayoutManager(context));

            SQLiteOpenHelper sqLiteOpenHelper = new SQLiteOpenHelper(
                    this.getContext(), "client.db");

            SQLiteDatabase sqLiteDatabase = sqLiteOpenHelper.getReadableDatabase();
            String query = "SELECT * FROM word ORDER BY name ASC"; // No trailing ';'
            Cursor cursor = sqLiteDatabase.rawQuery(query, null);


            recyclerView.setAdapter(new MySearchItemRecyclerViewAdapter(context, cursor));
        }
        return view;
    }


    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof IOnListFragmentInteractionListener) {
            mListener = (IOnListFragmentInteractionListener) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnListFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }
}

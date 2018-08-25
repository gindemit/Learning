package com.gindemit.dictionary.custom_view;

import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.gindemit.dictionary.R;

public class SearchField extends LinearLayout
        implements TextWatcher, View.OnClickListener {

    private EditText mEditText;
    private ImageView mImageView;

    public SearchField(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();
        mEditText = findViewById(R.id.search_edit_text);
        mImageView = findViewById(R.id.search_clear_button);

        mEditText.addTextChangedListener(this);
        mImageView.setOnClickListener(this);
    }

    @Override
    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

    }

    @Override
    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
        updateClearIconState(charSequence);
    }

    @Override
    public void afterTextChanged(Editable editable) {

    }

    private void updateClearIconState(CharSequence charSequence) {
        if(charSequence.toString().trim().length()==0){
            mImageView.setVisibility(View.GONE);
        } else {
            mImageView.setVisibility(View.VISIBLE);
        }
    }

    @Override
    public void onClick(View view) {
        mEditText.setText("");
    }
}

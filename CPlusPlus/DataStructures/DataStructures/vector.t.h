#pragma once
#include <iostream>
#include <cassert>
#include "vector.h"


namespace gindemit::test_vector
{
    using gindemit::vector;

    template<typename T>
    void print_vector(::gindemit::vector<T> v)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            ::std::cout << v[i] << " ";
        }
        ::std::cout << (v.size() == 0 ? "empty" : "") << ::std::endl;
    }

    void creation_test()
    {
        vector<int> v;
        assert(v.size() == 0);
        print_vector(v);

        vector<int> v_cap(8);
        assert(v_cap.size() == 0);
        print_vector(v_cap);

        vector<int> v_fill(34, 7);
        assert(v_fill.size() == 34);
        print_vector(v_fill);
    }

    void push_back_test()
    {
        vector<int> v;
        for (int i = 0; i < 20; ++i)
        {
            v.push_back(i);
        }
        assert(v.size() == 20);
        print_vector(v);
    }

    void change_items_test()
    {
        vector<int> v(15, 7);
        for (int i = 0; i < v.size(); i += 2)
        {
            v[i] = i;
            assert(v[i] == i);
        }
        print_vector(v);
    }

    void pop_back_test()
    {
        vector<int> v(20, 7);
        assert(v.size() == 20);
        print_vector(v);
        assert(v.pop_back() == 7);
        assert(v.size() == 19);
        print_vector(v);
    }

    void all_tests()
    {
        creation_test();
        push_back_test();
        change_items_test();
    }
}
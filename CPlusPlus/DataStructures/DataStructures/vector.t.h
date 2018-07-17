#pragma once
#include <iostream>
#include "vector.h"


namespace gindemit::test_vector
{
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
        gindemit::vector<int> v;
        print_vector(v);

        gindemit::vector<int> v_cap(8);
        print_vector(v_cap);

        gindemit::vector<int> v_fill(34, 7);
        print_vector(v_fill);
    }

    void all_tests()
    {
        creation_test();
    }
}
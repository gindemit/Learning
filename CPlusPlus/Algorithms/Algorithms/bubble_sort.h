#pragma once
#include "iter_swap.h"

// Example of work the bubble sort algorithm on vector<int> vi{3, 2, 1, 5, 4};
//          3      2      1      5      4
//00       s,f
//10        s      f
//          2      3      1      5      4
//11              s,f
//20        s             f
//          1      3      2      5      4
//21               s      f
//          1      2      3      5      4
//22                     s,f
//30        s                    f
//31               s             f
//32                      s      f
//33                            s,f
//40        s                           f
//41               s                    f
//42                      s             f
//43                             s      f
//          1       2     3      4      5
//44                                   s,f


template<typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (Iterator first = begin; first != end; ++first)
    {
        for (Iterator second = begin; second != first; ++second)
        {
            if (*second > *first)
            {
                iter_swap(first, second);
            }
        }
    }
}

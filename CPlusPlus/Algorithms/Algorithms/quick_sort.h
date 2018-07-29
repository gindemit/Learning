#pragma once
#include "iter_swap.h"


// Example of work the quick sort algorithm on vector<int> vi{3, 2, 1, 5, 4};
//                  3      2      1      5      4
//p00             b,i,j                         p      e
//                  3      2      1      5      4
//p01               b     i,j                   p      e
//                  3      2      1      5      4
//p02               b            i,j            p      e
//                  3      2      1      5      4
//p03               b                   i,j     p      e
//p04               b                    i     j,p     e
//                  3      2      1      4      5
//p10             b,i,j           p      e
//p11              b,i     j      p      e
//p12              b,i           j,p     e
//p12              b,i            p     j,e
//                  1      2      3      4      5
//q20              b,e
//                  1      2      3      4      5
//p20                    b,i,j    p      e
//                  1      2      3      4      5
//p21                      b    i,j,p    e
//                  1      2      3      4      5
//p30                   b,i,j,p   e
//                  1      2      3      4      5
//p40                                        b,i,j,p    e


template<typename TIterator>
TIterator partition(TIterator begin, TIterator end)
{
    TIterator pivot = end - 1;
    TIterator i = begin;
    for (TIterator j = begin; j != end; ++j)
    {
        if (*j < *pivot)
        {
            iter_swap(i++, j);
        }
    }
    iter_swap(i, pivot);
    return i;
}

template<typename TIterator>
void quick_sort(TIterator begin, TIterator end)
{
    if (begin != end)
    {
        TIterator pivot = partition(begin, end);
        quick_sort(begin, pivot);
        quick_sort(++pivot, end);
    }
}
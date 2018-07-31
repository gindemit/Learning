#pragma once
#include "iter_swap.h"


template<typename TIterator>
void bubble_sort(TIterator begin, TIterator end)
{
    if (begin == end)
    {
        return;
    }
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        TIterator it = begin;
        TIterator it_prev = begin;
        ++it;
        for (; it != end; ++it, ++it_prev)
        {
            if (*it_prev > *it)
            {
                iter_swap(it_prev, it);
                swapped = true;
            }
        }
        --end;
    }
}

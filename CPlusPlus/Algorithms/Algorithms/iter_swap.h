#pragma once

template<typename TIterator>
void iter_swap(TIterator first, TIterator second)
{
    typename TIterator::value_type temp = *first;
    *first = *second;
    *second = temp;
}
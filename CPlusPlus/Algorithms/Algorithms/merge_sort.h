#pragma once
#include <functional>
#include <vector>

template<typename TIterator>
static ::std::vector<typename TIterator::value_type> merge(TIterator begin, TIterator middle, TIterator end)
{
    TIterator left = begin;
    TIterator right = middle;
    ::std::vector<typename TIterator::value_type> sorted;

    while (left != middle && right != end)
    {
        sorted.emplace_back((*left < *right) ? *left++ : *right++);
    }
    sorted.insert(sorted.end(), left, middle);
    sorted.insert(sorted.end(), right, end);
    return sorted;
}

template<typename TIterator>
static void merge_sort_internal(TIterator begin, TIterator end)
{
    auto distance = ::std::distance(begin, end);
    if (distance < 2)
    {
        return;
    }
    TIterator middle = begin;
    ::std::advance(middle, distance / 2);
    merge_sort_internal(begin, middle);
    merge_sort_internal(middle, end);
    ::std::vector<typename TIterator::value_type> merged = merge(begin, middle, end);
    ::std::move(merged.cbegin(), merged.cend(), begin);
}

template<typename TIterator>
void merge_sort(TIterator begin, TIterator end)
{
    if (begin != end)
    {
        merge_sort_internal(begin, end);
    }
}
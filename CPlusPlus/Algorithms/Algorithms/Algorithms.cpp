// Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iterator>
#include <iostream>
#include "bubble_sort.h"
#include "quick_sort.h"


int main()
{
    ::std::vector<int> vi{ 3,2,1,5,4 };
    ::std::cout << "vector: ";
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(::std::cout, " "));

    quick_sort(vi.begin(), vi.end());
    ::std::cout << "\nsorted: ";
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(::std::cout, " "));

    return 0;
}


#pragma once
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <ctime>
#include <cstdlib>


using ::std::vector;
using ::std::cout;
using ::std::endl;
using ::std::cin;

void use_vector()
{
    vector<int> ints(10);
    ::std::iota(ints.begin(), ints.end(), 1);
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;
    ::std::copy(ints.crbegin(), ints.crend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 1 2 3 4 5 6 7 8 9 10
    // 10 9 8 7 6 5 4 3 2 1
}

void reverse_vector()
{
    vector<int> ints(10);
    ::std::iota(ints.begin(), ints.end(), 1);
    ::std::reverse(ints.rbegin(), ints.rend());
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 10 9 8 7 6 5 4 3 2 1
}

void use_fill()
{
    vector<int> eights(10);
    ::std::fill(eights.begin(), eights.end(), 8);
    ::std::copy(eights.cbegin(), eights.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 8 8 8 8 8 8 8 8 8 8
}

void use_fill_last_four()
{
    vector<int> eights(10);
    ::std::fill(eights.end() - 4, eights.end(), 8);
    ::std::copy(eights.cbegin(), eights.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 0 0 0 0 0 0 8 8 8 8
}

void use_fill_n()
{
    vector<int> sevens(10);
    ::std::fill_n(sevens.begin() + 1, 3, 7);
    ::std::copy(sevens.cbegin(), sevens.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 0 7 7 7 0 0 0 0 0 0
}

void use_random_shuffle()
{
    ::std::srand(static_cast<unsigned int>(::std::time(0)));
    vector<int> ints(10);
    ::std::iota(ints.begin(), ints.end(), 1);
    ::std::random_shuffle(ints.begin(), ints.end(), [](int i) { return ::std::rand() % i; });
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 3 5 9 8 7 4 6 10 2 1
}

void use_sort_after_random_shuffle()
{
    vector<int> ints(20);
    ::std::iota(ints.begin(), ints.end(), 1);
    ::std::random_shuffle(ints.begin(), ints.end(), [](int i) { return ::std::rand() % i; });
    cout << "shuffled vector: " << endl;
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;
    ::std::sort(ints.begin(), ints.end());
    cout << "after sort: " << endl;
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // shuffled vector:
    // 13 2 10 3 1 12 8 20 5 16 19 6 15 14 11 17 7 4 9 18
    // after sort :
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
}

void use_iterator_distance()
{
    vector<int> ints(20);
    ::std::iota(ints.begin(), ints.end(), 1);
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << "\tdistance: " << ::std::distance(ints.begin(), ints.end()) << endl;
    auto found = ::std::find(ints.cbegin(), ints.cend(), 7);
    ints.erase(found, found + 3);
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << "\t\tdistance: " << ::std::distance(ints.begin(), ints.end()) << endl;

    // Output:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20      distance: 20
    // 1 2 3 4 5 6 10 11 12 13 14 15 16 17 18 19 20            distance : 17
}

void use_count()
{
    vector<int> ints(20);
    ::std::iota(ints.begin(), ints.end() - ::std::distance(ints.cbegin(), ints.cend()) / 2, 1);
    ::std::iota(ints.end() - ::std::distance(ints.cbegin(), ints.cend()) / 2, ints.end(), 1);
    cout << "count of 1: " << ::std::count(ints.cbegin(), ints.cend(), 1) << endl;    
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // count of 1: 2
    // 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10
}

void use_generate()
{
    ::std::srand(static_cast<unsigned int>(::std::time(0)));
    vector<int> ints(20);
    ::std::generate(ints.begin(), ints.end(), []() { return ::std::rand() % 20; });

    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 10 7 5 11 13 14 14 7 8 7 13 9 3 12 19 6 1 14 15 11
}

void use_generate_and_count()
{
    ::std::srand(static_cast<unsigned int>(::std::time(0)));
    vector<int> ints(20);
    ::std::generate(ints.begin(), ints.end(), []() { return ::std::rand() % 20; });
    ::std::copy(ints.cbegin(), ints.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;
    int i = ::std::rand() % 20;
    cout << "count of " << i << ": " << ::std::count(ints.begin(), ints.end(), i) << endl;

    // Output:
    // 11 1 15 18 19 3 17 14 17 9 5 7 0 0 16 13 10 7 1 2
    // count of 5: 1
}
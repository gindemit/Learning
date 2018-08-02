#pragma once
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <list>

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

void use_swap_iterators()
{
    vector<int> vector_one(20);
    ::std::iota(vector_one.begin(), vector_one.end(), 1);

    vector<int> vector_two(20);
    ::std::iota(vector_two.rbegin(), vector_two.rend(), 1);

    cout << "vector_one: ";
    ::std::copy(vector_one.cbegin(), vector_one.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << "\nvector_two: ";
    ::std::copy(vector_two.cbegin(), vector_two.cend(), ::std::ostream_iterator<int>(cout, " "));

    ::std::iter_swap(vector_one.begin() + 3, vector_two.begin() + 7);

    cout << "\nafter iter_swap\nvector_one: ";
    ::std::copy(vector_one.cbegin(), vector_one.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << "\nvector_two: ";
    ::std::copy(vector_two.cbegin(), vector_two.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;

    // Output:
    // vector_one: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    // vector_two : 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
    // after iter_swap
    // vector_one : 1 2 3 13 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    // vector_two : 20 19 18 17 16 15 14 4 12 11 10 9 8 7 6 5 4 3 2 1
}

void use_adjacent_find()
{
    vector<int> vi(20);
    ::std::iota(vi.begin(), vi.end(), 1);

    vector<int>::const_iterator it = ::std::adjacent_find(vi.cbegin(), vi.cend());
    assert(it == vi.end());

    ::std::replace(vi.begin(), vi.end(), 8, 7);
    it = ::std::adjacent_find(vi.cbegin(), vi.cend());
    assert(it != vi.end());
    cout << "found adjacent iterator: " << *it << endl;
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // found adjacent iterator: 7
    // 1 2 3 4 5 6 7 7 9 10 11 12 13 14 15 16 17 18 19 20
}

void use_all_of()
{
    vector<int> vector_one(20, 9);
    vector<int> vector_two(20);
    ::std::iota(vector_two.begin(), vector_two.end(), 1);

    cout << "all of vector_one are a multiple of three: " << ((::std::all_of(vector_one.cbegin(), vector_one.cend(), [](int item) { return item % 3 == 0; }) != 0) ? " yes!" : " no!") << endl;
    cout << "all of vector_two are a multiple of three: " << ((::std::all_of(vector_two.cbegin(), vector_two.cend(), [](int item) { return item % 3 == 0; }) != 0) ? " yes!" : " no!") << endl;

    // Output:
    // all of vector_one are a multiple of three:  yes!
    // all of vector_two are a multiple of three : no!
}

void use_binary_search()
{
    vector<int> vi(20);
    ::std::iota(vi.begin(), vi.end(), 1);
    cout << "vector has value '7': " << ((::std::binary_search(vi.cbegin(), vi.cend(), 7) != 0) ? " yes!" : " no!") << endl;

    // Output:
    // vector has value '7':  yes!
}

void use_copy_if()
{
    vector<int> vi(20);
    ::std::iota(vi.begin(), vi.end(), 1);
    ::std::copy_if(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "), [](int item) { return item % 2 == 0; });
    cout << endl;

    ::std::ofstream file("even_numbers.txt", ::std::ofstream::out);
    ::std::copy_if(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(file, " "), [](int item) { return item % 2 == 0; });
    file.close();

    // Output:
    // 2 4 6 8 10 12 14 16 18 20
}

void use_assign()
{
    vector<int> vi(20);
    ::std::iota(vi.begin(), vi.end(), 1);
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;

    int values[] = { 2,1,4,3,6,5,8,7,9 };
    vi.assign(values, values + 9);
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));

    // Output:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    // 2 1 4 3 6 5 8 7 9
}

void use_make_heap()
{
    vector<int> vi(20);
    ::std::iota(vi.begin(), vi.end(), 1);
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;
    std::make_heap(vi.begin(), vi.end());
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;
    ::std::iota(vi.rbegin(), vi.rend(), 1);
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;
    std::make_heap(vi.begin(), vi.end());
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    cout << endl;

    // Output:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    // 20 19 15 18 11 13 14 17 9 10 2 12 6 3 7 16 8 4 1 5
}

void use_greather_and_less()
{
    ::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
    ::std::vector<int> vi(20);
    ::std::generate(vi.begin(), vi.end(), []() { return ::std::rand() % 20; });
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    std::sort(vi.begin(), vi.end(), ::std::greater<int>());
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;


    std::sort(vi.begin(), vi.end(), ::std::less<int>());
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    // Output:
    // 18 15 13 7 13 4 13 11 7 7 9 16 15 6 1 1 16 17 16 16
    // 18 17 16 16 16 16 15 15 13 13 13 11 9 7 7 7 6 4 1 1
    // 1 1 4 6 7 7 7 9 11 13 13 13 15 15 16 16 16 16 17 18
}

void use_back_inserter()
{
    ::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
    ::std::vector<int> vi(20);
    ::std::generate(vi.begin(), vi.end(), []() { return ::std::rand() % 20; });
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    ::std::vector<int> second;

    ::std::copy_if(vi.cbegin(), vi.cend(), ::std::back_inserter(second), [](int item) { return item > 10; });
    ::std::copy(second.cbegin(), second.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    // Output:
    // 0 4 7 13 17 7 11 7 8 18 19 15 15 2 8 17 11 0 5 0
    // 13 17 11 18 19 15 15 17 11
}

void use_front_inserter()
{
    ::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
    ::std::vector<int> vi(20);
    ::std::generate(vi.begin(), vi.end(), []() { return ::std::rand() % 20; });
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    ::std::list<int> second; // supports push_front operation

    ::std::copy_if(vi.cbegin(), vi.cend(), ::std::front_inserter(second), [](int item) { return item > 10; });
    ::std::copy(second.cbegin(), second.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    // Output:
    // 15 14 5 3 12 10 2 3 8 11 14 0 0 11 19 19 12 8 6 15
    // 15 12 19 19 11 14 11 12 14 15
}

void use_inserter()
{
    ::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
    ::std::vector<int> vi(20);
    ::std::generate(vi.begin(), vi.end(), []() { return ::std::rand() % 20; });
    ::std::copy(vi.cbegin(), vi.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    ::std::vector<int> second;

    ::std::copy_if(vi.cbegin(), vi.cend(), ::std::inserter(second, second.begin()), [](int item) { return item > 10; });
    ::std::copy(second.cbegin(), second.cend(), ::std::ostream_iterator<int>(cout, " "));
    ::std::cout << ::std::endl;

    // Output:
    // 9 7 12 11 14 5 0 17 16 16 18 6 10 2 13 13 18 18 9 6
    // 12 11 14 17 16 16 18 13 13 18 18
}
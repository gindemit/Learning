#pragma once
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using ::std::cout;
using ::std::endl;
using ::std::map;
using ::std::make_pair;

struct Foo
{
private:
    int _value;

public:
    Foo(int value) :
        _value(value)
    {
    }

    friend ::std::ostream &operator<<(::std::ostream &os, const Foo &foo)
    {
        return os << foo._value;
    }
};

using IntFooPair = ::std::pair<const int, Foo>;

::std::ostream &operator<<(::std::ostream &os, const IntFooPair &pair)
{
    return os << "{" << pair.first << ", " << pair.second << "}, ";
}

void fill(map<int, Foo> &m)
{
    m.insert(make_pair(7, 7));
    m.emplace(0, 0);
    m.emplace(4, 4);
    m.emplace(2, 2);
    m.emplace(2, 2);
    m.emplace(3, 3);
    m.emplace(1, 1);
}

void create_add_items()
{
    map<int, Foo> m;
    fill(m);
    ::std::copy(m.cbegin(), m.cend(), ::std::ostream_iterator<IntFooPair>(cout));
    cout << endl;
    // Output:
    // {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {7, 7},
}

void use_iterators()
{
    map<int, Foo> m;
    fill(m);
    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
        cout << "{" << it->first << ", " << it->second << "}, ";
    }
    cout << endl;
    // Output:
    // {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {7, 7},
}

void use_reverse_iterators()
{
    map<int, Foo> m;
    fill(m);
    for (auto it = m.crbegin(); it != m.crend(); ++it)
    {
        cout << "{" << it->first << ", " << it->second << "}, ";
    }
    cout << endl;
    // Output:
    // {7, 7}, {4, 4}, {3, 3}, {2, 2}, {1, 1}, {0, 0},
}
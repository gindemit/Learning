#pragma once
#include <iostream>
#include <map>
#include <iterator>

using ::std::cout;
using ::std::endl;
using ::std::map;
using ::std::make_pair;

struct Foo
{
    int Value;
    Foo(int value) :
        Value(value)
    {
    }
};

using IntFooPair = ::std::pair<int, Foo>;

::std::ostream &operator<<(::std::ostream &os, const IntFooPair &pair)
{
    return os << "key: " << pair.first << ", value: " << pair.second.Value << endl;
}

void create_add_items()
{
    map<int, Foo> m;

    m.insert(make_pair(7, 7));
    m.emplace(0, 0);
    m.emplace(4, 4);
    m.emplace(2, 2);
    m.emplace(2, 2);
    m.emplace(3, 3);
    m.emplace(1, 1);

    ::std::copy(m.cbegin(), m.cend(), ::std::ostream_iterator<IntFooPair>(cout));
}
#pragma once
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using ::std::cout;
using ::std::endl;
using ::std::map;
using ::std::make_pair;

struct CharFoo
{
private:
    char _value;

public:
    CharFoo(char value) :
        _value(value)
    {
    }

    friend ::std::ostream &operator<<(::std::ostream &os, const CharFoo &foo)
    {
        return os << foo._value;
    }
};

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
using UintCharPair = ::std::pair<const unsigned int, CharFoo>;

::std::ostream &operator<<(::std::ostream &os, const IntFooPair &pair)
{
    return os << "{" << pair.first << ", " << pair.second << "}, ";
}

::std::ostream &operator<<(::std::ostream &os, const UintCharPair &pair)
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

void use_uint_char_map()
{
    map<unsigned int, char> m;

    m.emplace(1, 'D');
    m.emplace(2, 'A');
    m.emplace(3, 'D');
    m.emplace(4, 'A');
    m.emplace(5, 'D');

    ::std::copy(m.cbegin(), m.cend(), ::std::ostream_iterator<UintCharPair>(cout));

    // Output:
    // {1, D}, {2, A}, {3, D}, {4, A}, {5, D},
}

void use_equal_range()
{
    map<unsigned int, char> m;

    m.emplace(1, 'D');
    m.emplace(2, 'A');
    m.emplace(3, 'D');
    m.emplace(4, 'A');
    m.emplace(5, 'D');

    auto found = m.equal_range(2);
    ::std::copy(found.first, found.second, ::std::ostream_iterator<UintCharPair>(cout));
    cout << endl;

    auto notFound = m.equal_range(6);
    ::std::copy(notFound.first, notFound.second, ::std::ostream_iterator<UintCharPair>(cout));
    cout << endl;

    // Output:
    // {2, A},
    // 
}

void use_upper_bound()
{
    map<unsigned int, char> m;

    m.emplace(1, 'D');
    m.emplace(2, 'A');
    m.emplace(3, 'D');
    m.emplace(4, 'A');
    m.emplace(5, 'D');
    m.emplace(8, 'D');
    m.emplace(7, 'D');
    m.emplace(6, 'D');

    auto upper = m.upper_bound(2);
    ::std::copy(upper, m.end(), ::std::ostream_iterator<UintCharPair>(cout));
    cout << endl;

    upper = m.upper_bound(4);
    ::std::copy(upper, m.end(), ::std::ostream_iterator<UintCharPair>(cout));
    cout << endl;

    // Output:
    // {3, D}, {4, A}, {5, D}, {6, D}, {7, D}, {8, D},
    // {5, D}, {6, D}, {7, D}, {8, D},
}

void use_lower_bound()
{
    map<unsigned int, char> m;

    m.emplace(1, 'D');
    m.emplace(2, 'A');
    m.emplace(3, 'D');
    m.emplace(4, 'A');
    m.emplace(5, 'D');
    m.emplace(8, 'D');
    m.emplace(7, 'D');
    m.emplace(6, 'D');

    auto lower = m.lower_bound(2);
    ::std::copy(lower, m.end(), ::std::ostream_iterator<UintCharPair>(cout));
    cout << endl;

    lower = m.lower_bound(4);
    ::std::copy(lower, m.end(), ::std::ostream_iterator<UintCharPair>(cout));
    cout << endl;

    // Output:
    // {2, A}, {3, D}, {4, A}, {5, D}, {6, D}, {7, D}, {8, D},
    // {4, A}, {5, D}, {6, D}, {7, D}, {8, D},
}

void use_key_comp()
{
    map<unsigned int, char> m;
    auto key_comp = m.key_comp();
    cout << key_comp(1, 5) << endl;
    cout << key_comp(5, 1) << endl;
    cout << key_comp(5, 5) << endl;

    // Output:
    // 1
    // 0
    // 0
}

void use_max_size()
{
    map<unsigned int, char> m;
    cout << m.max_size() << endl;

    // Output:
    // 178956970
}
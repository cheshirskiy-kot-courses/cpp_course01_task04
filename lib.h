#pragma once

#include <iostream>
#include <map>

#include <range/v3/all.hpp>
namespace rs = ranges;
namespace rv = ranges::views;
namespace ra = ranges::actions;

#include "custom_allocator.h"


struct hard
{
    int fa;
    int fi;
    hard(int fa, int fi): fa(fa), fi(fi) {};

    hard(const hard &) = delete;
    hard(hard &&) = delete;
};

constexpr bool operator== (const hard & h0, const hard & h1) noexcept
{
    return (h0.fa == h1.fa) && (h0.fi == h1.fi);
}


int factorial(const int N);
int fibonacci(const int N);


template<class Allocator>
void print_map(std::map<int, hard, std::less<int>, Allocator> m)
{
    auto print_pair =
        [](auto & p) {
            std::cout
                << p.first << " "
                << p.second.fa << " "
                << p.second.fi
                << std::endl;
        };

    print_pair(rs::front(m));
    rs::for_each(m | rv::tail, print_pair);
}


template<class Allocator = std::allocator<std::pair<const int, hard>>>
auto create_map()
{
    auto m =
        rv::iota(0, 10) |
        rv::transform(
            [](int x)
            {
                return std::pair(x, hard{ factorial(x), fibonacci(x) });
            }) |
        rs::to<std::map<int, hard, std::less<int>, Allocator>>;

    return m;
}


using MAP_0 = std::map<int, hard>;

using CA = CustomAllocator < std::pair<const int, hard>>;
using MAP_1 = std::map<int, hard, std::less<int>, CA>;

MAP_0 create_map_0();
MAP_1 create_map_1();

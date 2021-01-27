#pragma once

#include <iostream>
#include <map>

#include <range/v3/all.hpp>
namespace rs = ranges;
namespace rv = ranges::views;
namespace ra = ranges::actions;

#include "custom_allocator.h"
#include "custom_container.h"


struct hard
{
    int fa;
    int fi;
    hard(int fa, int fi): fa(fa), fi(fi) {};

    hard(const hard &) = delete;
    hard(hard &&) noexcept = delete;
};

constexpr bool operator== (const hard & h0, const hard & h1) noexcept
{
    return (h0.fa == h1.fa) && (h0.fi == h1.fi);
}


int factorial(const int N);
int fibonacci(const int N);


template<class Alloc>
void print_map(const std::map<int, hard, std::less<int>, Alloc> & m)
{
    rs::for_each(m, [](auto & p) {
            std::cout
                << p.first << " "
                << p.second.fa << " "
                << p.second.fi
                << std::endl;
        });
    std::cout << std::endl;
}


template<class Alloc>
void print_custom_container(const CustomContainer<hard, Alloc> & m)
{
    rs::for_each(m, [](auto & p) {
        std::cout
            << p.fa << " "
            << p.fi
            << std::endl;
        });
    std::cout << std::endl;
}


template<class Alloc>
void generate_map(std::map<int, hard, std::less<int>, Alloc> & m)
{
    rs::for_each(
        rv::iota(0, 10),
        [&m](int i) {
            m.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(i),
                std::forward_as_tuple(factorial(i), fibonacci(i))
            );
        });
}


template<class Alloc>
void generate_container(CustomContainer<hard, Alloc> & m)
{
    rs::for_each(
        rv::iota(0, 10),
        [&m](int i) { m.emplace(factorial(i), fibonacci(i)); });
}


using Map_0 = std::map<int, hard>;

using CA_0 = CustomAllocator<std::pair<const int, hard>>;
using Map_1 = std::map<int, hard, std::less<int>, CA_0>;

using Container_0 = CustomContainer<hard>;

using CA_1 = CustomAllocator<hard>;
using Container_1 = CustomContainer<hard, CA_1>;

Map_0 create_map_0();
Map_1 create_map_1();
Container_0 create_container_0();
Container_1 create_container_1();

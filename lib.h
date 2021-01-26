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


template<
    template<class ...> class Container, class ...Parameters>
void print_map(const Container<Parameters...> & m)
{
    rs::for_each(m, [](auto & p) {
            std::cout
                << p.first << " "
                << p.second.fa << " "
                << p.second.fi
                << std::endl;
        });
}


using MAP_0 = std::map<int, hard>;

using CA_1 = CustomAllocator < std::pair<const int, hard>>;
using MAP_1 = std::map<int, hard, std::less<int>, CA_1>;

using MAP_2 = CustomContainer<hard>;

using CA_3 = CustomAllocator<hard>;
using MAP_3 = CustomContainer<hard, CA_3>;

MAP_0 create_map_0();
MAP_1 create_map_1();
MAP_2 create_map_2();
MAP_3 create_map_3();

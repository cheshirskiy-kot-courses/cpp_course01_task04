#include "lib.h"


int factorial(const int N)
{
    if (N == 0) return 1;
    return N * factorial(N - 1);
}

int fibonacci(const int N)
{
    if (N == 0) return 0;
    else if (N == 1) return 1;
    else return fibonacci(N - 1) + fibonacci(N - 2);
}

MAP_0 create_map_0()
{
    MAP_0 m;

    rs::for_each(
        rv::iota(0, 10),
        [&m](int i) {
            m.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(i),
                std::forward_as_tuple(factorial(i), fibonacci(i))
            );
        });

    return m;
}

MAP_1 create_map_1()
{

    MAP_1 m(CA_1{ 10 });

    rs::for_each(
        rv::iota(0, 10),
        [&m](int i) {
            m.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(i),
                std::forward_as_tuple(factorial(i), fibonacci(i))
            );
        });

    return m;
}

MAP_2 create_map_2()
{
    MAP_2 m;

    rs::for_each(
        rv::iota(0, 10),
        [&m](int i) { m.emplace(factorial(i), fibonacci(i)); });

    return m;
}

MAP_3 create_map_3()
{
    MAP_3 m(CA_3{ 10 });

    rs::for_each(
        rv::iota(0, 10),
        [&m](int i) { m.emplace(factorial(i), fibonacci(i)); });

    return m;
}

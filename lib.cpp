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

    for (int i = 0; i < 10; i++) {
        m.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(i),
            std::forward_as_tuple(factorial(i), fibonacci(i))
        );
    }

    return m;
}

MAP_1 create_map_1()
{

    MAP_1 m(CA{ 10 });

    for (int i = 0; i < 10; i++) {
        m.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(i),
            std::forward_as_tuple(factorial(i), fibonacci(i))
        );
    }

    return m;
}

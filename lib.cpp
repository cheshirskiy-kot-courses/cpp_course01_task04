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

Map_0 create_map_0()
{
    Map_0 m;
    generate_map(m);
    return m;
}

Map_1 create_map_1()
{
    Map_1 m(CA_0{ 9 });
    generate_map(m);
    return m;
}

Container_0 create_container_0()
{
    Container_0 m;
    generate_container(m);
    return m;
}

Container_1 create_container_1()
{
    Container_1 m(CA_1{ 9 });
    generate_container(m);
    return m;
}

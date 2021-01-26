#include "lib.h"


int main(int argc, char const * argv[])
{
    {
        // создание экземпляра std::map<int, hard>
        print_map(create_map_0());
    }

    {
        // создание экземпляра std::map<int, hard>
        // с новым аллокатором ограниченным 10 элементами
        print_map(create_map_1());
    }

    {
        // создание экземпляра своего контейнера для хранения hard
        print_custom_container(create_map_2());
    }

    {
        // создание экземпляра своего контейнера для хранения hard
        // с новым аллокатором ограниченным 10 элементами
        print_custom_container(create_map_3());
    }
}
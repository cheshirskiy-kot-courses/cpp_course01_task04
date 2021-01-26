#include "lib.h"


int main(int argc, char const * argv[])
{
    // создание экземпляра std::map<int, hard>
    print_map(create_map_0());
    std::cout << std::endl;

    // создание экземпляра std::map<int, hard>
    // с новым аллокатором ограниченным 10 элементами
    print_map(create_map_1());
    std::cout << std::endl;

    // создание экземпляра своего контейнера для хранения hard

    // создание экземпляра своего контейнера для хранения hard
    // с новым аллокатором ограниченным 10 элементами
}
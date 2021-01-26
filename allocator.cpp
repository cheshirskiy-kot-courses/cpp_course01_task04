﻿#include "lib.h"


int main(int argc, char const * argv[])
{
    {
        // создание экземпляра std::map<int, hard>
        print_map(create_map_0());
        std::cout << std::endl;
    }

    {
        // создание экземпляра std::map<int, hard>
        // с новым аллокатором ограниченным 10 элементами
        print_map(create_map_1());
        std::cout << std::endl;
    }

    //{
    //    // создание экземпляра своего контейнера для хранения hard
    //    print_map(create_map_2());
    //    std::cout << std::endl;
    //}

    // создание экземпляра своего контейнера для хранения hard
    // с новым аллокатором ограниченным 10 элементами

    // Контейнер имеет публичный и приватный интерфейсы.
    // Реализованы копирующий и перемещающий конструкторы при совпадении типа аллокатора.
    // Реализованы копирующий и перемещающий конструкторы при отличающихся типах аллокатора.
    // Аллокатор может расширяться с шагом 10. В коде все циклы увеличены на 1, чтобы спровоцировать расширение
}
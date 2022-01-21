//
// Created by salim on 21/01/2022.
//
#include "algorithmsPCH.hpp"
#include "SortSubRange.hpp"

namespace algofun
{

    void sortsubrangeTest()
    {
        std::puts("--sortsubrangeTest--");

        std::vector vec1 = {1,55,77,4,67,99,1,310, 25};
        std::puts("before sortsubrangeTest: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        sortSubrange(vec1.begin(), vec1.end(),vec1.begin()+3, vec1.begin()+5);

        std::puts("after sortsubrangeTest: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::printf("subrange begin: %i, subrange last value: %i \n", *(vec1.begin()+3), *(vec1.begin()+5-1));
        std::puts("--Tests Passed--");
        std::puts("--------------------");

    }




}
//
// Created by salim on 10/01/2022.
//

#include "algorithmsPCH.hpp"
#include "AlgoFindMissingElem.hpp"



namespace algofun
{

    void AlgoFun_Test()
    {
        std::puts("--AlgoFun_Test--");
        std::vector<unsigned> vecOdd = {3,1,2,5,7,8,6};
        std::vector<unsigned> vecEven = {1,2,3,4,6,7};
        std::vector<unsigned >vecTwoGaps = {3,2,1,5,7,9,6,10,1,13};
        std::printf("vecOdd end : %d \n", *(vecOdd.data()+vecOdd.size()-1));

        auto valueOdd = find_missing_element(vecOdd.begin(), vecOdd.end());
        auto valueEven=find_missing_element(vecEven.begin(), vecEven.end());
        printf("vecOdd Missing Elem (expected: [4]): %d \n", valueOdd);
        printf("vecEven Missing Elem (expected: [5]): %d \n", valueEven);

        auto valueTwoGaps = find_missing_element(vecTwoGaps.data(), (vecTwoGaps.data()+vecTwoGaps.size() ));
        printf("vecTwoGaps Missing Elem (expected: [4 or 8]): %d \n", valueTwoGaps);
    }




}



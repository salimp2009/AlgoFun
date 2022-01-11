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
        std::vector<unsigned> vecOdd = {1,2,3,5,6,7,8};
        std::vector<unsigned> vecEven = {1,2,3,4,6,7};
        std::vector vecTwoGaps = {1,2,3,5,6,7,9,10,1,13};
        std::printf("vecOdd end : %d \n", *(vecOdd.data()+vecOdd.size()-1));

        auto valueOdd = find_missing_element(&vecOdd[0], &(vecOdd[vecOdd.size()-1]));
        auto valueEven=find_missing_element(vecEven.data(), (vecEven.data()+vecEven.size()-1));
        printf("vecOdd Missing Elem (expected: [4]: %d \n", valueOdd);
        printf("vecEven Missing Elem (expected: [5]: %d \n", valueEven);


    }




}



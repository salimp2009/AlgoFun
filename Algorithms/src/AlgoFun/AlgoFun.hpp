//
// Created by salim on 10/01/2022.
//

#ifndef ALGOFUN_ALGOFUN_HPP
#define ALGOFUN_ALGOFUN_HPP

#include "../algorithmsPCH.hpp"
#include "SortSubRange.hpp"


namespace algofun {
    void AlgoFun_Test();
    void minabsent_Tests();
    void minabsentVersion2_Tests();
    void setSymmetric_difference_Test();
    void slideAlgorithm_Test();
    void slideWithRanges_Test();
    void slideRight_Test();
    void slideLeft_Test();
    void gather_Test();
    void gatherRange_Test();
    void stablePartition_Position();
    void sortsubrangeTest();
    void accumlateN_Test();
    void accumlateN_ChronoDur_Test();
    void accumulate_iterTest();
    void foldleft_Test();
    void reducepar_Test();
    void stablePartitionBuffer_Test();


    struct Person {
        std::string name{};
        int confID{};
    };


}// namespace algofun

#endif//ALGOFUN_ALGOFUN_HPP

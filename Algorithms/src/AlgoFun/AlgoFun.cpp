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
        std::vector<unsigned> vecOdd = {0,3,1,2,5,7,8,6};
        std::vector<unsigned> vecEven = {0,1,2,3,4,6,7};
        std::vector<unsigned >vecTwoGaps = {3,2,1,5,7,9,6,10,1,13};
        std::printf("vecOdd end : %d \n", *(vecOdd.data()+vecOdd.size()-1));

        auto valueOdd = min_absent(vecOdd.begin(), vecOdd.end());
        auto valueEven=min_absent(vecEven.begin(), vecEven.end());
        printf("vecOdd Missing Elem (expected: [4]): %d \n", valueOdd);
        printf("vecEven Missing Elem (expected: [5]): %d \n", valueEven);

        auto valueTwoGaps = min_absent(vecTwoGaps.data(), (vecTwoGaps.data()+vecTwoGaps.size()),1u);
        printf("vecTwoGaps Missing Elem (expected: [4 or 8]): %d \n", valueTwoGaps);
    }

    void minabsent_Tests()
    {

        std::puts("--minabsent_Tests--");
        using namespace std::chrono_literals;

        std::vector<std::chrono::seconds> vec1={0s, 1s, 3s, 2s, 5s};
        assert(min_absent(vec1.begin(), vec1.end())==4s);
        using T = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;

        std::vector vec2 ={T{0s}, T{1s}, T{3s}, T{2s}, T{5s}};
        assert(min_absent(vec2.begin(),vec2.end())==T{4s});

        // same as above but a new type in C++20
        using T1= std::chrono::sys_time<std::chrono::seconds>;
        std::vector vec3 ={T1{0s}, T1{1s}, T1{3s}, T1{2s}, T1{5s}};
        assert(min_absent(vec3.begin(),vec3.end())==T1{4s});
        std::puts("--Tests Passes--");
        std::puts("--------------------");
    }

    void minabsentVersion2_Tests()
    {

        std::puts("--minabsentVersion2_Tests--");
        using namespace std::chrono_literals;

        std::vector<std::chrono::seconds> vec1={0s, 1s, 3s, 2s, 5s};
        auto result1= min_absent2(vec1.begin(), vec1.end());
        assert(result1==4s);
        std::printf("result1: %lld s \n", result1.count());

        using T = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
        std::vector vec2 ={T{0s}, T{1s}, T{3s}, T{2s}, T{5s}};
        auto result2 = min_absent2(vec2.begin(),vec2.end());
        assert(result2==T{4s});
        std::printf("result2: %lld s \n", result2.time_since_epoch().count());


        // same as above but a new type in C++20
        using T1= std::chrono::sys_time<std::chrono::seconds>;
        std::vector vec3 ={T1{0s}, T1{1s}, T1{3s}, T1{2s}, T1{5s}};
        assert(min_absent2(vec3.begin(),vec3.end())==T1{4s});
        std::puts("--Tests Passed--");
        std::puts("--------------------");
    }





}// end of namespace



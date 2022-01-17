//
// Created by salim on 10/01/2022.
//

#include "algorithmsPCH.hpp"
#include "AlgoFindMissingElem.hpp"
#include "SlideAlgorithm.hpp"
#include "GatherAlgorithm.hpp"


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
        std::puts("--Tests Passed--");
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

    void setSymmetric_difference_Test()
    {
        std::puts("--set_symmetric_difference--");
        // Computes symmetric difference of two sorted ranges: the elements that are found in either of the ranges,
        // but not in both of them are copied to the range beginning at d_first. The resulting range is also sorted.
        std::vector v1 = {1,2,3,4,5,6,7,8     };
        std::vector v2 = {        5,  7,  9,10};
        std::ranges::sort(v1);
        std::ranges::sort(v2);
        std::vector<int> v_symDifference;
        std::ranges::set_symmetric_difference(v1.begin(), v1.end(),  v2.begin(), v2.end(), std::back_inserter(v_symDifference));

        //
        std::printf("the diff between v1 and v2 : [expected : 1,2,3,4,6,8,9,10]; \nresult: ");
        for(auto&& elem : v_symDifference)
        {
            std::printf(" %i ", elem );
        }
        std::puts("\n[Tests Passed]");
        std::puts("--------------------");
    }

    void slideAlgorithm_Test()
    {
        std::puts("--slideAlgorithm_Test--");

        std::vector vec1 = {1,3,4,2, 66, 102,88, 55,105,99};
        auto first =vec1.begin()+2;
        auto last = vec1.begin()+6; // this 1 past the last vaule
        auto position =std::next(vec1.begin(),8);
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::printf("original: orig_begin: %i, orig_end: %i, orig_position: %i \n", *first, *(last-1), *(position-1));

        auto result = slide(first, last, position);
        std::printf("slide: new_begin: %i, new_end: %i \n", *(result.first), *(result.second-1));

        std::printf("slide: new_begin_dist: %lli, new_end_dist: %lli \n", std::distance(vec1.begin(),result.first)+1, std::distance(vec1.begin(),result.second));

        std::printf("after slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }

        std::puts("\n[Tests Passed]");
        std::puts("--------------------");
    }

    void slideWithRanges_Test()
    {
        std::puts("--slideWithRanges_Test--");
        std::vector vec1 = {1,3,4,2, 66, 102,88, 55,105,99};
        std::printf("before slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }

        std::puts("");

        auto first =std::ranges::next(vec1.begin(), 2);
        auto last = std::ranges::next(vec1.begin(), 6);
        auto position =std::ranges::next(vec1.begin(),8);

        // FIXME: red squiggles might be false error; check it in compiler explorer
        std::ranges::subrange slideRange{first, last};
        auto slideResult = slide(slideRange, position);
        std::printf("after slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::printf("slide: new_begin: %i, new_end: %i \n", *slideResult.begin(), *(slideResult.end()-1));

        std::span slideSpan{vec1.begin()+2, vec1.begin()+6 };

        // FIXME: red squiggles might be false error; check it in compiler explorer
        slide(slideRange, position);
        std::printf("after 2nd slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");
    }

    void slideRight_Test()
    {
        std::puts("--slideRight_Test--");

        std::vector vec1 = {1,3,4,2, 66, 102,88, 55,105,99};
        std::printf("before slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");

        slide_right(vec1.begin()+2, vec1.begin()+6, 3u);
        std::printf("after slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }

        std::puts("");
    }

    void slideLeft_Test()
    {
        std::puts("--slideLeft_Test--");
        std::vector vec1 = {1,3,4,2, 66, 102,88, 55,105,99};
        std::printf("before slide: ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");

        slide_left(vec1.begin()+4, vec1.begin()+8, 2u);
        std::printf("after slide left ");
        for(auto elem :vec1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::list list1 = {1,3,4,2, 66, 102,88, 55,105,99};
        std::printf("list 1; before slide: ");
        for(auto elem :list1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");

        auto first = std::next(list1.begin(), 4);
        auto last = std::next(list1.begin(), 8);

        // supports at least std::bidirectional_iterator; does not work for forward list
        // use regular slide with position to slide
        slide_left(first, last, 2u);
        std::printf("list 1; after slide: ");
        for(auto elem :list1)
        {
            std::printf("%i ", elem);
        }
        std::puts("");
    }





    }// end of namespace



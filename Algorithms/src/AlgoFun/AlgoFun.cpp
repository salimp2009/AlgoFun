//
// Created by salim on 10/01/2022.
//

#include "AlgoFun.hpp"
#include "../algorithmsPCH.hpp"
#include "AlgoFindMissingElem.hpp"
#include "GatherAlgorithm.hpp"
#include "SlideAlgorithm.hpp"
#include "StablePartitionPosition.hpp"
#include "accumulate_iter.hpp"
#include "accumulate_n.hpp"
#include "algoConcepts.hpp"
#include "fold_left.hpp"
#include "reduce_par.hpp"
#include "stable_partitionPos.hpp"
#include "stable_partitionUserBuffer.hpp"


namespace algofun {

    void AlgoFun_Test() {
        std::puts("--AlgoFun_Test--");
        std::vector<unsigned> vecOdd = {0, 3, 1, 2, 5, 7, 8, 6};
        std::vector<unsigned> vecEven = {0, 1, 2, 3, 4, 6, 7};
        std::vector<unsigned> vecTwoGaps = {3, 2, 1, 5, 7, 9, 6, 10, 1, 13};
        std::printf("vecOdd end : %d \n", *(vecOdd.data() + vecOdd.size() - 1));

        auto valueOdd = min_absent(vecOdd.begin(), vecOdd.end());
        auto valueEven = min_absent(vecEven.begin(), vecEven.end());
        printf("vecOdd Missing Elem (expected: [4]): %d \n", valueOdd);
        printf("vecEven Missing Elem (expected: [5]): %d \n", valueEven);

        auto valueTwoGaps = min_absent(vecTwoGaps.data(), (vecTwoGaps.data() + vecTwoGaps.size()), 1u);
        printf("vecTwoGaps Missing Elem (expected: [4 or 8]): %d \n", valueTwoGaps);
    }

    void minabsent_Tests() {
        std::puts("--minabsent_Tests--");
        using namespace std::chrono_literals;

        std::vector<std::chrono::seconds> vec1 = {0s, 1s, 3s, 2s, 5s};
        assert(min_absent(vec1.begin(), vec1.end()) == 4s);
        using T = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;

        std::vector vec2 = {T{0s}, T{1s}, T{3s}, T{2s}, T{5s}};
        assert(min_absent(vec2.begin(), vec2.end()) == T{4s});

        // same as above but a new type in C++20
        using T1 = std::chrono::sys_time<std::chrono::seconds>;
        std::vector vec3 = {T1{0s}, T1{1s}, T1{3s}, T1{2s}, T1{5s}};
        assert(min_absent(vec3.begin(), vec3.end()) == T1{4s});
        std::puts("--Tests Passed--");
        std::puts("--------------------");
    }

    void minabsentVersion2_Tests() {
        std::puts("--minabsentVersion2_Tests--");
        using namespace std::chrono_literals;

        std::vector<std::chrono::seconds> vec1 = {0s, 1s, 3s, 2s, 5s};
        auto result1 = min_absent2(vec1.begin(), vec1.end());
        assert(result1 == 4s);
        std::printf("result1: %lld s \n", result1.count());

        using T = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
        std::vector vec2 = {T{0s}, T{1s}, T{3s}, T{2s}, T{5s}};
        auto result2 = min_absent2(vec2.begin(), vec2.end());
        assert(result2 == T{4s});
        std::printf("result2: %lld s \n", result2.time_since_epoch().count());


        // same as above but a new type in C++20
        using T1 = std::chrono::sys_time<std::chrono::seconds>;
        std::vector vec3 = {T1{0s}, T1{1s}, T1{3s}, T1{2s}, T1{5s}};
        assert(min_absent2(vec3.begin(), vec3.end()) == T1{4s});
        std::puts("--Tests Passed--");
        std::puts("--------------------");
    }

    void setSymmetric_difference_Test() {
        std::puts("--set_symmetric_difference--");
        // Computes symmetric difference of two sorted ranges: the elements that are found in either of the ranges,
        // but not in both of them are copied to the range beginning at d_first. The resulting range is also sorted.
        std::vector v1 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::vector v2 = {5, 7, 9, 10};
        std::ranges::sort(v1);
        std::ranges::sort(v2);
        std::vector<int> v_symDifference;
        std::ranges::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v_symDifference));

        //
        std::printf("the diff between v1 and v2 : [expected : 1,2,3,4,6,8,9,10]; \nresult: ");
        for (auto &&elem: v_symDifference) {
            std::printf(" %i ", elem);
        }
        std::puts("\n[Tests Passed]");
        std::puts("--------------------");
    }

    void slideAlgorithm_Test() {
        std::puts("--slideAlgorithm_Test--");

        std::vector vec1 = {1, 3, 4, 2, 66, 102, 88, 55, 105, 99};
        auto first = vec1.begin() + 2;
        auto last = vec1.begin() + 6;// this 1 past the last vaule
        auto position = std::next(vec1.begin(), 8);
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::printf("original: orig_begin: %i, orig_end: %i, orig_position: %i \n", *first, *(last - 1), *(position - 1));

        auto result = slide(first, last, position);
        std::printf("slide: new_begin: %i, new_end: %i \n", *(result.first), *(result.second - 1));

        std::printf("slide: new_begin_dist: %lli, new_end_dist: %lli \n", std::distance(vec1.begin(), result.first) + 1, std::distance(vec1.begin(), result.second));

        std::printf("after slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }

        std::puts("\n[Tests Passed]");
        std::puts("--------------------");
    }

    void slideWithRanges_Test() {
        std::puts("--slideWithRanges_Test--");
        std::vector vec1 = {1, 3, 4, 2, 66, 102, 88, 55, 105, 99};
        std::printf("before slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }

        std::puts("");

        auto first = std::ranges::next(vec1.begin(), 2);
        auto last = std::ranges::next(vec1.begin(), 6);
        auto position = std::ranges::next(vec1.begin(), 8);

        // FIXME: red squiggles might be false error; check it in compiler explorer
        std::ranges::subrange slideRange{first, last};
        auto slideResult = slide(slideRange, position);
        std::printf("after slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::printf("slide: new_begin: %i, new_end: %i \n", *slideResult.begin(), *(slideResult.end() - 1));

        std::span slideSpan{vec1.begin() + 2, vec1.begin() + 6};

        // FIXME: red squiggles might be false error; check it in compiler explorer
        slide(slideRange, position);
        std::printf("after 2nd slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");
    }

    void slideRight_Test() {
        std::puts("--slideRight_Test--");

        std::vector vec1 = {1, 3, 4, 2, 66, 102, 88, 55, 105, 99};
        std::printf("before slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        slide_right(vec1.begin() + 2, vec1.begin() + 6, 3u);
        std::printf("after slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }

        std::puts("");
    }

    void slideLeft_Test() {
        std::puts("--slideLeft_Test--");
        std::vector vec1 = {1, 3, 4, 2, 66, 102, 88, 55, 105, 99};
        std::printf("before slide: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        slide_left(vec1.begin() + 4, vec1.begin() + 8, 2u);
        std::printf("after slide left ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::list list1 = {1, 3, 4, 2, 66, 102, 88, 55, 105, 99};
        std::printf("list 1; before slide: ");
        for (auto elem: list1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        auto first = std::next(list1.begin(), 4);
        auto last = std::next(list1.begin(), 8);

        // supports at least std::bidirectional_iterator; does not work for forward list
        // use regular slide with position to slide
        slide_left(first, last, 2u);
        std::printf("list 1; after slide: ");
        for (auto elem: list1) {
            std::printf("%i ", elem);
        }
        std::puts("");
    }

    void gather_Test() {
        std::puts("--gather_Test--");
        std::vector vec1 = {1, 3, 4, 2, 5, 102, 88, 55, 104, 98};
        std::printf("before gather: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        auto result1 = gather(vec1.begin(), vec1.end(), vec1.begin() + 5, [](auto elem) { return elem % 2 != 0; });

        std::printf("vec1; after gather: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");
        const auto gatherBegin = std::ranges::distance(vec1.begin(), result1.first);
        const auto gatherEnd = std::ranges::distance(vec1.begin(), result1.second);

        std::printf("gather pos begin: %lli, gather pos end: %lli \n", gatherBegin, gatherEnd);
        std::puts("");

        // Test if the position == vec1.begin()
        auto result2 = gather(vec1.begin(), vec1.end(), vec1.begin(), [](auto elem) { return elem % 2 != 0; });
        std::printf("vec1; after gather at top: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");
        std::printf("gather top; begin: %i, end: %i \n", *result2.first, *(result2.second - 1));
    }

    void gatherRange_Test() {
        std::puts("--gatherRange_Test--");
        std::vector vec1 = {1, 3, 4, 2, 5, 102, 88, 55, 104, 98};
        std::printf("before gather Range: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");
        // std::ranges::subrange gatherRange{vec1.begin(), vec1.end()};
        auto position = std::ranges::next(vec1.begin(), 4);

        auto result2 = gather(vec1, position, [](auto elem) { return elem % 2 != 0; });

        std::printf("vec1; after gatherRange: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        const auto gatherBegin = std::ranges::distance(vec1.begin(), result2.begin());
        const auto gatherEnd = std::ranges::distance(vec1.begin(), result2.end());

        std::printf("gather pos begin: %lli, gather pos end: %lli \n", gatherBegin, gatherEnd);
        std::puts("");

        std::vector<Person> vec2 = {{"Sean", 1}, {"Salim", 9}, {"Didem", 52}, {"Ben", 2}, {"Kim", 8}};
        std::printf("before gather Range: ");
        for (const auto &elem: vec2) {
            std::printf("[%s, ID: %i] ", elem.name.c_str(), elem.confID);
        }
        std::puts("\n---------------------------------------------");

        auto conferencePos = std::next(vec2.begin(), 2);
        auto confPriority = [](auto elem) { return elem < 3; };
        auto resultConf = gather(vec2, conferencePos, confPriority, &Person::confID);

        std::printf("after gather Range: ");
        for (const auto &elem: vec2) {
            std::printf("[%s, ID: %i] ", elem.name.c_str(), elem.confID);
        }
        std::puts("\n---------------------------------------------");

        // FIXME: use fmt library !!!
        std::printf("gather pos begin: %s, gather pos end: %s \n", (resultConf.begin())->name.c_str(), (resultConf.end() - 1)->name.c_str());
        std::puts("");
    }

    void stablePartition_Position() {
        std::puts("--stablePartion_PositionSelect--");
        std::vector vec1 = {1, 3, 4, 2, 5, 102, 88, 55, 104, 98};
        const std::vector positionSelect = {0, 1, 0, 1, 0, 0, 1, 0, 0, 0};
        std::puts("before stablePartitionPosition: ");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        [[maybe_unused]] auto p = stablePartitionPosition(std::begin(vec1), std::end(vec1), [&](auto It) {
            return *(std::next(std::begin(positionSelect), std::distance(vec1.begin(), It)));
        });

        std::puts("after stablePartitionPosition:");
        for (auto elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::vector vec2 = {1, 3, 4, 2, 5, 102, 88, 55, 104, 98};

        // FIXME : non recursive version but does not work correctly !!
        stablePartitionPosition2(std::begin(vec2), std::end(vec2), [&](auto It) {
            return *(std::next(std::begin(positionSelect), std::distance(vec2.begin(), It)));
        });

        std::puts("after stablePartitionPosition2:");
        for (auto elem: vec2) {
            std::printf("%i ", elem);
        }
        std::puts("");
    }

    void accumlateN_Test() {
        std::puts("--accumlateN_Test--");
        std::vector vec1 = {1, 3, 4, 10, 10, 15, 20, 35};

        const auto [sum0, position0] = accumulate_n(std::begin(vec1), std::end(vec1), 15u, 0, [](const auto &init, const auto &elem) { return init + elem; });
        std::printf("sum0: %i, Counted upto: %lli \n", sum0, std::distance(vec1.begin(), position0) + 1);

        // NOTE: red squiggles showing wrong error due to clang-tidy/clang is behind C++20
        int sum2 = 0;
        for (const auto &elem: vec1 | std::ranges::views::take(4)) {
            sum2 += elem;
        }
        std::printf("sum2: %i \n", sum2);

        const auto [sum1, position1] = accumulate_n(vec1, 15u, 0, [](auto init, const auto &elem) { return init + elem; });
        std::printf("ranges version: sum1: %i, Counted upto: %lli \n", sum1, std::distance(vec1.begin(), position1) + 1);
        std::puts("");

        const auto [sum3, position3] = accumulate_n(vec1.begin(), vec1.end(), 4u);
        std::printf("default predicate + default initial version: sum3: %i, Counted upto: %lli \n", sum3, std::distance(vec1.begin(), position3) + 1);
        std::puts("");
    }

    void accumlateN_ChronoDur_Test() {
        std::puts("--accumlateN_Chrono Duration_Test--");

        using namespace std::chrono_literals;

        std::vector vec1 = {1s, 3s, 4s, 10s, 10s, 15s, 20s, 35s};
        std::printf("originaldurations(seconds): ");
        for (const auto &elem: vec1) {
            std::printf(" -> %lli sec ", elem.count());
        }

        std::puts(" ");

        const auto [sum1, position1] = accumulate_n(std::cbegin(vec1), std::cend(vec1), 4u, 0s, [](auto &&init, const auto &elem) { return init + elem; });
        std::printf("\nduration version: sum1: %lli, Counted upto: %lli \n", sum1.count(), std::distance(vec1.cbegin(), position1) + 1);
        std::puts("");

        const auto [sum2, position2] = accumulate_n(std::cbegin(vec1), std::cend(vec1), 4u);
        std::printf("duration with default plus<>: sum2: %lli, Counted upto: %lli \n", sum2.count(), std::distance(vec1.cbegin(), position2) + 1);
        std::puts("");

        const auto [sum3, position3] = accumulate_n(vec1, 15u, 0s, [](auto &&init, const auto &elem) { return std::move(init + elem); });
        std::printf("ranges duration version: sum3: %lli, Counted upto: %lli \n", sum3.count(), std::distance(vec1.begin(), position3) + 1);
    }


    void accumulate_iterTest() {
        std::puts("--accumulate_iterTest--");
        std::vector vec1 = {1, 3, 4, 10, 10, 15, 20, 3};
        auto sum1 = accumulate_iter(vec1, 0, [](auto &&init, auto currentIter) { return init + *currentIter; });
        std::printf("accumulate _iter; range version: [expected: 66]: %i \n", sum1);

        using namespace std::chrono_literals;
        std::vector vec2 = {1s, 3s, 4s, 10s, 10s, 15s, 20s, 3s};
        auto sum2 = accumulate_iter(vec2, 0s, [](auto &&init, auto currentIter) { return init + *currentIter; });
        std::printf("accumulate_iter with chrono dur: [expected: 66]: %lli \n", sum2.count());

        std::puts("--Tests Passed--");
    }

    void foldleft_Test() {
        std::puts("--foldleft_Test--");
        std::vector vec1 = {1, 3, 4, 10, 10, 15, 20, 3};
        const auto result = fold_left(std::ranges::begin(vec1), std::ranges::end(vec1), 0.0, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("fold_left with int vec and double initial value : %f \n", result);

        const auto result_range = fold_left(vec1, 0.0, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("fold_left Ranges with int vec and double initial value : %f \n", result_range);

        std::vector vec2 = {1.0, 3.0, 4., 10., 10., 15., 20., 3.5};
        const auto result2 = fold_left(std::ranges::begin(vec2), std::ranges::end(vec2), 0, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("fold_left with double vec and int initial value : %f \n", result2);

        using namespace std::chrono_literals;
        std::vector vec3 = {1s, 3s, 4s, 10s, 10s, 15s, 20s, 3s};

        const auto result3 = fold_left(std::ranges::begin(vec3), std::ranges::end(vec3), 0s, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("fold_left with chrono int and chrono int initial value : %lli\n", result3.count());

        const auto result_range2 = fold_left(vec3, 0.0s, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("fold_left Ranges with chrono int and chrono double initial value : %Lf\n", result_range2.count());

        //
        std::vector vec4 = {1.0s, 3.0s, 4.0s, 10.0s, 10.0s, 15.0s, 20.0s, 3.5s};

        const auto result4 = fold_left(std::ranges::begin(vec4), std::ranges::end(vec4), 0s, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("fold_left Ranges with chrono double and chrono int initial value : %Lf\n", result4.count());
    }

    void reducepar_Test() {
        std::puts("--reducepar_Test--");
        std::vector vec1 = {1, 3, 4, 10, 10, 15, 20, 3};
        const auto result5 = reduce_par(std::ranges::begin(vec1), std::ranges::end(vec1), 0, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("reduce_par with int and double initial value : %i\n", result5);

        using namespace std::chrono_literals;
        std::vector vec2 = {1.0s, 3.0s, 4.0s, 10.0s, 10.0s, 15.0s, 20.0s, 3.5s};
        const auto result2 = reduce_par(std::ranges::begin(vec2), std::ranges::end(vec2), 0s, [](auto &&accum, const auto &elem) { return accum + elem; });
        std::printf("reduce_par with chrono double and chrono int initial value : %Lf\n", result2.count());
        //std::ranges::stable_partition()
    }

    void stablePartitionBuffer_Test() {
        std::puts("--stablePartitionBuffer_Test--");
        std::vector vec1{3, 5, 6, 7, 8, 9, 15};
        auto even = [](const auto &elem) { return elem % 2 == 0; };
        std::ranges::stable_partition(vec1, even);
        for (const auto &elem: vec1) {
            std::printf("%i ", elem);
        }
        std::puts("");

        std::vector vec2{3, 5, 6, 7, 8, 9, 15};
        stable_partitionBuffer(vec2, even);
        for (const auto &elem: vec2) {
            std::printf("%i ", elem);
        }
        std::puts("");
    }

}// namespace algofun

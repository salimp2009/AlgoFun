
#include "algorithmsPCH.hpp"
#include "AlgoFun/AlgoFun.hpp"

template<class I, class P>
auto any_of3(I f, I l, P p)
{
    return std::reduce(f, l, false,
                       [p](auto a, auto b) { return a || p(b); });
}


int main()
{
    algofun::AlgoFun_Test();
    algofun::minabsent_Tests();
    algofun::minabsentVersion2_Tests();
    algofun::setSymmetric_difference_Test();
    algofun::slideAlgorithm_Test();
    algofun::slideWithRanges_Test();
    algofun::slideRight_Test();
    algofun::slideLeft_Test();
    algofun::gather_Test();
    algofun::gatherRange_Test();
    algofun::stablePartition_Position();
    algofun::sortsubrangeTest();
    algofun::anyofFast_Test();

    // for testing purposes
    std::vector v = { 1, 2, 3 };
    auto x =  any_of3(std::begin(v), std::end(v), [](auto e) { return e == 3; });
    std::cout<<"any_of from main:"<< x<<'\n';


}

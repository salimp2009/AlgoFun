
#include "algorithmsPCH.hpp"
#include "AlgoFun/AlgoFun.hpp"
#include "AlgoFun/anyof.hpp"


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
    algofun::anyof_Test();


    // for testing purposes;
    // FIXME : this is not working when it is in the test function but
    //  any_of2 works when called from the main directly
   std::vector v = { 1, 2, 3 };
   auto xx = algofun::any_of2(v.begin(), v.end(), [](auto elem) { return elem==3;});
   std::printf("xx from main (anyof): %i \n", xx);


}

//
// Created by salim on 17/01/2022.
//

#ifndef ALGOFUN_GATHERALGORITHM_HPP
#define ALGOFUN_GATHERALGORITHM_HPP

#include "algorithmsPCH.hpp"

namespace  algofun
{

template<std::bidirectional_iterator It, std::indirect_unary_predicate<It> PredT>
constexpr std::pair<It, It> gather(It first, It last, It position, PredT pred)
{
    const auto notPred = [&]<typename... T>(T&&... elem)
    {
        auto result = pred(std::forward<T>(elem)...);
        return ! result;
    };
    return { std::stable_partition(first, position, (notPred)), std::stable_partition(position, last, pred)};
}



} // end of namespace

#endif //ALGOFUN_GATHERALGORITHM_HPP

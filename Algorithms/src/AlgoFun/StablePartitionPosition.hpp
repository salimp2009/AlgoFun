//
// Created by salim on 19/01/2022.
//

#ifndef ALGOFUN_STABLEPARTITIONPOSITION_HPP
#define ALGOFUN_STABLEPARTITIONPOSITION_HPP

#include "algorithmsPCH.hpp"

namespace algofun
{
    template<std::bidirectional_iterator It, std::invocable<It> PredT>
    constexpr auto stablePartitionPosition(It first, It last, PredT pred) ->It
    {
        // FIXME: try to turn this into while loop
        const auto n = std::distance(first, last);
        if (n==0) return first;

        // check predicate against iterator position not the value !!
        if (n==1) return first + std::invoke(pred, first);

        const auto mid = std::next(first,  n/2);
        return std::rotate(stablePartitionPosition(first,mid, pred ),
                           mid,
                           stablePartitionPosition(mid, last, pred));
    }



} // end of namespace

#endif //ALGOFUN_STABLEPARTITIONPOSITION_HPP

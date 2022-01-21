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
        // FIXME: try to turn this into while loop; implemented below but does not work properly !!
        // TODO: Add ranges version to it
        const auto n = std::distance(first, last);
        if (n==0) return first;

        // check predicate against iterator position not the value !!
        if (n==1) return first + std::invoke(pred, first);

        const auto mid = std::next(first,  n/2);
        return std::rotate(stablePartitionPosition(first,mid, pred ),
                           mid,
                           stablePartitionPosition(mid, last, pred));
    }

    // FIXME : non_recursive version: it does not work correctly YET :) !!
    template<std::bidirectional_iterator It, std::invocable<It> PredT>
    constexpr auto stablePartitionPosition2(It first, It last, PredT pred) ->It
    {
        // FIXME: these are some trial messy stuff :) !
        const auto n = std::distance(first, last);
        if (n==0) return first;

        It result= std::next(first);
        auto last2=std::next(first);
        while(last-first!=1)
        {
            // check predicate against iterator position not the value !!
            const auto first2 = first + std::invoke(pred, first);
            const auto mid = std::next(first2, std::distance(first2, last2)/2);
            last2 =std::next(mid);
            //const auto mid = std::next(first,  n/2);
            result = std::rotate(first2, mid, last2);
            ++first;
        }
        return result;
    }




} // end of namespace

#endif //ALGOFUN_STABLEPARTITIONPOSITION_HPP

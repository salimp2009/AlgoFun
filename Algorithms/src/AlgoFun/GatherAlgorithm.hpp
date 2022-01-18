//
// Created by salim on 17/01/2022.
//

#ifndef ALGOFUN_GATHERALGORITHM_HPP
#define ALGOFUN_GATHERALGORITHM_HPP

#include "algorithmsPCH.hpp"

namespace  algofun
{

template<std::ranges::bidirectional_range R, class Proj = std::identity,
        std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<R>, Proj>> Pred >
requires std::permutable<std::ranges::iterator_t<R>>
constexpr std::ranges::subrange<std::ranges::iterator_t<R>> gather(R&& rng, std::ranges::iterator_t<R> position, Pred pred, Proj proj={} )
{
    const auto notPred = [&]<typename T>(T&& elem)
    {
        // FIXME : test with a user defined class with 2 members to test the projection using members
        //auto result2 = std::invoke(pred, std::invoke(proj, elem));
        auto result = pred(std::forward<T>(elem));
        return ! result;
    };

    // FIXME: move these comments to doxygen to return type explanation
    // each stable_partitions .begin() is used because it gives the mid point as first iterator and last
    // is always the end of the range or the second group after the partition
    return {std::ranges::stable_partition(std::ranges::begin(rng), position, notPred, proj).begin(),
            std::ranges::stable_partition(position, std::ranges::end(rng), pred, proj).begin()
    };
}



template<std::bidirectional_iterator It, std::indirect_unary_predicate<It> PredT>
constexpr std::pair<It, It> gather(It first, It last, It position, PredT pred)
{
    const auto notPred = [&]<typename T>(T&& elem)
    {
        auto result = pred(std::forward<T>(elem));
        return ! result;
    };


    return { std::stable_partition(first, position, notPred), std::stable_partition(position, last, pred)};
}



} // end of namespace

#endif //ALGOFUN_GATHERALGORITHM_HPP

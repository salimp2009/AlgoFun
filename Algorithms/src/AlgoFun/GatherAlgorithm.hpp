//
// Created by salim on 17/01/2022.
//

#ifndef ALGOFUN_GATHERALGORITHM_HPP
#define ALGOFUN_GATHERALGORITHM_HPP

#include "algorithmsPCH.hpp"


namespace  algofun
{

/// @paragraph gather with std::ranges; moves disjointed selection (non-contiguous selection) of items in a container to around a pivot point
/// without changing the relative order of the items
/// @param  rng         is a range / container (with a begin / end, raw arrays are OK);
/// modeled around std::ranges::bidirectional_range & std::permutable<std::ranges::iterator_t<R>>
/// @param  position    pivot point to gather disjointed selections; iterator type has to match the type of Range above
/// @param  pred        predicate to apply on projected elements
/// @param  proj        projection to apply on projected elements
/// @returns  a subrange for the selected items ; avoids returning potentially dangling iterators or views by
/// modelling around std::ranges::borrowed_subrange_t<R>; see  https://en.cppreference.com/w/cpp/ranges/borrowed_iterator_t
/// @complexity sames as std::ranges::stable partition;  Given N = ranges::distance(first, last) at worst 2*N.log(N)
/// @swaps only O(N) swaps in case extra memory used in the std::ranges::stable_partition (may change with compiler implementations)
/// exactly 2N application of the predicate and projection since stable_partition is called twice

template<std::ranges::bidirectional_range R, class Proj = std::identity,
        std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<R>, Proj>> Pred >
requires std::permutable<std::ranges::iterator_t<R>>
constexpr std::ranges::borrowed_subrange_t<R> gather(R&& rng, std::ranges::iterator_t<R> position, Pred pred, Proj proj={} )
{
    const auto notPred = [&]<typename T>(T&& elem)->bool
    {
        auto result = pred(std::forward<T>(elem));
        return ! result;
    };

    // each stable_partitions .begin() is used because it gives the mid-point as first iterator and last
    // is always the end of the range or the second group after the partition
    return {std::ranges::stable_partition(std::ranges::begin(rng), position, notPred, proj).begin(),
            std::ranges::stable_partition(position, std::ranges::end(rng), pred, proj).begin()
    };
}

/// gather moves disjointed selection (non-contiguous selection) of items in a container to around a pivot point
/// without changing the relative order of the items
/// @param  first       start of a range/container (models around std::bidirectional_iterator)
/// @param  last        end of a range/container (it is one past the last value)
/// @param  position    pivot point to gather disjointed selections
/// @param  pred        predicate to apply on projected elements
/// @returns  a pair iterators std::pair<It, It> that point to new position of moved selection;
/// begin and end of the selected items
/// @complexity sames as std::ranges::stable partition;  Given N = ranges::distance(first, last) at worst 2*N.log(N)
/// @swaps only O(N) swaps in case extra memory used in the std::ranges::stable_partition
/// exactly 2N application of the predicate and projection since stable_partition is called twice

// FIXME: use std::ranges::stable_partition because std::pair is not constexpr yet !!
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

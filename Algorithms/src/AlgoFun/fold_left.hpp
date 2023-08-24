//
// Created by salim on 15/02/2022.
//

#ifndef ALGOFUN_FOLD_LEFT_HPP
#define ALGOFUN_FOLD_LEFT_HPP

#include "../algorithmsPCH.hpp"
#include "algoConcepts.hpp"
#include <functional>
namespace algofun {
    template<std::input_iterator I, std::sentinel_for<I> S, class T,
             details::indirectlyLeftFoldable<T, I> Op,
             class R = std::invoke_result_t<Op &, T, std::iter_reference_t<I>>>
    constexpr auto fold_left(I first, S last, T &&init, Op op) -> R {
        if (first == last) {
            return R(std::move(init));
        }

        auto accum = std::invoke(std::forward<Op>(op), std::move(init), *first);
        for (++first; first != last; ++first) {
            accum = std::invoke(std::forward<Op>(op), std::move(accum), *first);
        }

        return accum;
    }

    // FIXME: not sure if a projection make sense in accumulate; it makes sense
    //  if it is a predicate for selection of the items but accumulate over actual type value not the projection
    //  here it accumulates over the projection value that may not be the result wanted
    //  if user wants accumulate over the type (not the projected value) then no need to pass a projection
    template<std::ranges::input_range Range, class T, class Proj = std::identity,
             details::indirectlyLeftFoldable<T, std::projected<std::ranges::iterator_t<Range>, Proj>> Op = std::plus<>,
             class R = std::invoke_result_t<Op &, T, typename std::projected<std::ranges::iterator_t<Range>, Proj>::value_type>>
    constexpr auto fold_left(Range &&range, T &&init, Op op, Proj proj = {}) -> R {
        auto first = std::ranges::begin(range);
        const auto last = std::ranges::end(range);

        if (first == last) {
            return R(std::move(init));
        }

        auto accum = std::invoke(std::forward<Op>(op), std::move(init), std::invoke(proj, *first));
        for (++first; first != last; ++first) {
            accum = std::invoke(std::forward<Op>(op), std::move(accum), std::invoke(proj, *first));
        }

        return accum;
    }


}// namespace algofun


#endif//ALGOFUN_FOLD_LEFT_HPP

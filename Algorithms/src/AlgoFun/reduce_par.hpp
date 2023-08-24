//
// Created by salim on 15/02/2022.
//

#ifndef ALGOFUN_REDUCE_PAR_HPP
#define ALGOFUN_REDUCE_PAR_HPP

#include "../algorithmsPCH.hpp"
#include "fold_left.hpp"

namespace algofun {
    template<std::random_access_iterator I, std::sentinel_for<I> S, class T,
             details::indirectlyLeftFoldable<T, I> Op,
             class R = std::invoke_result_t<Op &, T, std::iter_reference_t<I>>>
        requires semigroup<R, Op, std::iter_reference_t<I>, std::iter_reference_t<I>> &&
                 semigroup<R, Op, R, R>
    constexpr auto reduce_par(I first, S last, T &&init, Op op) -> R {

        if (first == last) {
            return R(std::move(init));
        }

        auto accum = std::invoke(std::forward<Op>(op), std::move(init), *first);
        for (++first; last - first > 4; first += 4) {
            auto result1 = R(std::invoke(op, first[0], first[1]));
            auto result2 = R(std::invoke(op, first[2], first[3]));
            auto result3 = R(std::invoke(op, std::move(result1), std::move(result2)));
            accum = std::invoke(std::forward<Op>(op), std::move(accum), std::move(result3));
        }

        return fold_left(first, last, std::move(accum), std::ref(op));
    }


}// namespace algofun


#endif//ALGOFUN_REDUCE_PAR_HPP

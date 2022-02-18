//
// Created by salim on 15/02/2022.
//

#ifndef ALGOFUN_FOLD_LEFT_HPP
#define ALGOFUN_FOLD_LEFT_HPP

#include "algorithmsPCH.hpp"

namespace algofun
{
    // FIXME: add a range version and
    //  update the concept details::indirectlyLeftFoldable for projection
    template<std::input_iterator I, std::sentinel_for<I> S, class T,
            details::indirectlyLeftFoldable<T, I> Op,
            class R = std::invoke_result_t<Op&, T, std::iter_reference_t<I>>>
    constexpr auto  fold_left(I first, S last, T&& init, Op op) ->R
    {
        if(first == last)
        {
            return (std::move(init));
        }

        auto accum = std::invoke(std::forward<Op>(op), std::move(init), *first);
        for(++first; first != last; ++first)
        {
          accum = std::invoke(std::forward<Op>(op), std::move(accum), *first);
        }

        return accum;
    }









} // end of namespace





#endif //ALGOFUN_FOLD_LEFT_HPP

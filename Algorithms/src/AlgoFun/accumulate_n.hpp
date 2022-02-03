//
// Created by salim on 03/02/2022.
//

#ifndef ALGOFUN_ACCUMULATE_N_HPP
#define ALGOFUN_ACCUMULATE_N_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{
    template<std::input_iterator InputIt, std::unsigned_integral Size, typename T, std::predicate<T, std::iter_value_t<InputIt>> BinaryOp>
    constexpr auto accumulate_n(InputIt&& first,Size&& n, T&& init, BinaryOp&& op )-> std::pair<T, InputIt>
    {
        if(n==0) return {init, first};

        // FIXME: check if last and newinit can be constexpr without effecting return value optimization
        // FIXME: make a range version using views::take for n elements
        auto last =std::ranges::next(first, n);
        auto newinit = std::accumulate(first, last, std::move(init), std::move(op));

        return {newinit, last};
    }

    // FIXME: test this might more optimized !!
    template<std::input_iterator InputIt, std::unsigned_integral Size, typename T, std::predicate<T, std::iter_value_t<InputIt>> BinaryOp>
    constexpr auto accumulate_nAlt(InputIt&& first,Size&& n, T&& init, BinaryOp&& op )-> std::pair<T, InputIt>
    {
        if(n==0) return {init, first};

        for(; n>0; --n, ++first)
        {
            init +=std::invoke(std::forward<BinaryOp>(op), std::move(init), *first);
        }
        return {init, first};
    }

}
















#endif //ALGOFUN_ACCUMULATE_N_HPP

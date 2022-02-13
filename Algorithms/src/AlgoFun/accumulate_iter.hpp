//
// Created by salim on 11/02/2022.
//

#ifndef ALGOFUN_ACCUMULATE_ITER_HPP
#define ALGOFUN_ACCUMULATE_ITER_HPP

#include "algorithmsPCH.hpp"
#include "accumulate_n.hpp"

namespace algofun
{

    /// * accumulate_iter is a helper function that operates on iterator without dereferencing to be able to implement other algorithms

    template<std::ranges::input_range Range, std::movable T=std::ranges::range_reference_t<Range>,
            std::regular_invocable<T, std::ranges::iterator_t<Range>> BinaryOp>
    inline constexpr auto accumulate_iter(Range&& range, T&& init, BinaryOp op)->T
    {
        auto first = std::ranges::begin(range);
        auto last = std::ranges::end(range);
        if(first==last) return std::forward<T>(init);

        for(;first!=last; ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), first);
        }

        return std::forward<T>(init);
    }


    template<std::input_iterator InputIt, std::movable T=std::iter_value_t<InputIt> ,
            std::regular_invocable<T, InputIt> BinaryOp>
    inline constexpr auto accumulate_iter(InputIt first, InputIt last, T&& init, BinaryOp op)-> T
    {
        if(first==last) return std::forward<T>(init);

        for(;first!=last; ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), first);
        }
        return std::forward<T>(init);
    }





} //end of namespace

#endif //ALGOFUN_ACCUMULATE_ITER_HPP

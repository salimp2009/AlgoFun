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


    // FIXME: Test ; Not sure if regular_invocable will work;
    //  it might be changed to iterator_value_t<iterator_t<Range>> or ranges_value_t<Range>
    template<std::ranges::input_range Range, typename T,
            std::regular_invocable<T, std::ranges::iterator_t<Range>> BinaryOp>
    inline constexpr auto accumulate_iter(Range&& range, T&& init, BinaryOp op)->T
    {
        auto first = std::ranges::begin(range);
        auto last = std::ranges::end(range);
        if(first==last) return {std::forward<T>(init)};

        for(;first!=last; ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), first);
        }

        return {std::forward<T>(init)};
    }


    // FIXME: Test ; Not sure if regular_invocable will work;
    //  it might be changed to iterator_value_t<iterator_t<Range>>
    template<std::input_iterator InputIt, typename T=std::iter_value_t<InputIt> ,
            std::regular_invocable<T, InputIt> BinaryOp>
    inline constexpr auto accumulate_iter(InputIt first, InputIt last, T init, BinaryOp op)-> T
    {
        if(first==last) return {std::move(init)};

        for(;first!=last; ++first)
        {
            init =std::invoke(std::move(op), std::move(init), first);
        }
        return {std::move(init)};
    }





} //end of namespace

#endif //ALGOFUN_ACCUMULATE_ITER_HPP

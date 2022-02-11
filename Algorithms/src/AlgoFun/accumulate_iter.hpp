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
            std::regular_invocable<T, std::ranges::iterator_t<Range>> BinaryOp=std::plus<>>
    inline constexpr auto accumulate_iter(Range&& range, T&& init=T{}, BinaryOp op={})-> std::pair<T, std::ranges::iterator_t<Range>>
    {
        auto first = std::ranges::begin(range);
        auto last = std::ranges::end(range);
        if(first==last) return {std::forward<T>(init), first};

        for(;first!=last; ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), first);
        }

        return {std::forward<T>(init), first};
    }


    // FIXME: Test ; Not sure if regular_invocable will work;
    //  it might be changed to iterator_value_t<iterator_t<Range>>
    template<std::input_iterator InputIt, typename T=std::iter_value_t<InputIt> ,
            std::regular_invocable<T, InputIt> BinaryOp=std::plus<>>
    inline constexpr auto accumulate_iter(InputIt first, InputIt last, T init=T{}, BinaryOp op={})-> std::pair<T, InputIt>
    {
        if(first==last) return {std::move(init), first};

        for(;first!=last; ++first)
        {
            init =std::invoke(std::move(op), std::move(init), first);
        }
        return {std::move(init), first};
    }





} //end of namespace

#endif //ALGOFUN_ACCUMULATE_ITER_HPP

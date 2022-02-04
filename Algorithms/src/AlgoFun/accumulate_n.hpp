//
// Created by salim on 03/02/2022.
//

#ifndef ALGOFUN_ACCUMULATE_N_HPP
#define ALGOFUN_ACCUMULATE_N_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{

    // FIXME : add inputIT last so we check against
    template<typename T>
    concept unsignedInt = std::is_unsigned_v<T>;

    template<std::input_iterator InputIt, unsignedInt Size, typename T, std::predicate<T, std::iter_value_t<InputIt>> BinaryOp>
    constexpr auto accumulate_n(InputIt&& first,Size&& n, T&& init, BinaryOp&& op )-> std::pair<T, InputIt>
    {
        if(n==0) return {init, first};

        auto last =std::ranges::next(first, n);
        init = std::accumulate(first, last, std::move(init), std::move(op));

        return {std::move(init), last};
    }

    // FIXME: Range version; needs testing
    template<std::ranges::input_range Range, unsignedInt Size, typename T, class Proj=std::identity,
             std::predicate<T, std::iter_value_t<std::ranges::iterator_t<Range>>> BinaryOp>
    constexpr auto accumulate_nR(Range&& range, Size&& n, T&& init, BinaryOp&& op, Proj&& proj={} )-> std::pair<T, std::ranges::iterator_t<Range>>
    {
        auto first = std::ranges::begin(range);
        if(n==0) return {std::move(init), first};

        n =std::ranges::min(n, std::ranges::size(range));
        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::move(init), std::invoke(proj, *first));
        }

        return {std::move(init), first};
    }

    // FIXME: test this might more optimized !!
    template<std::input_iterator InputIt, std::unsigned_integral Size, typename T, std::predicate<T, std::iter_value_t<InputIt>> BinaryOp>
    constexpr auto accumulate_nAlt(InputIt&& first,Size&& n, T&& init, BinaryOp&& op )-> std::pair<T, InputIt>
    {
        if(n==0) return {std::move(init), first};

        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::move(init), *first);
        }
        return {std::move(init), first};
    }

}
















#endif //ALGOFUN_ACCUMULATE_N_HPP

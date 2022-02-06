//
// Created by salim on 03/02/2022.
//

#ifndef ALGOFUN_ACCUMULATE_N_HPP
#define ALGOFUN_ACCUMULATE_N_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{

    // FIXME : make unsigned convertible
    template<typename T>
    concept unsignedType = std::is_unsigned_v<T>;




    // FIXME: test this; std::indirect_binary_predicate<T*,std::projected<std::ranges::iterator_t<Range>, Proj>
    template<std::ranges::input_range Range, unsignedType Size, typename T, class Proj=std::identity,
             std::predicate<T, typename std::projected<std::ranges::iterator_t<Range>, Proj>::value_type> BinaryOp>
    inline constexpr auto accumulate_n(Range&& range, Size&& n, T&& init, BinaryOp&& op, Proj&& proj={} )-> std::pair<T, std::ranges::iterator_t<Range>>
    {
        auto first = std::ranges::begin(range);
        if(n==0) return {std::forward<T>(init), first};

        // FIXME: try to find a simple shorter way
        n =static_cast<Size>(std::ranges::min(static_cast<std::ranges::range_difference_t<Range>>(n), std::ranges::ssize(range)));
        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), std::invoke(proj, *first));
        }

        return {std::forward<T>(init), first};
    }


    template<std::input_iterator InputIt, unsignedType Size, typename T, std::predicate<T, std::iter_value_t<InputIt>> BinaryOp>
    inline constexpr auto accumulate_n(InputIt first, InputIt last, Size&& n, T init, BinaryOp op )-> std::pair<T, InputIt>
    {
        if(n==0) return {std::move(init), first};
        const auto originalsize = std::distance(first, last);
        n = static_cast<Size>(std::min(std::distance(first, std::next(first,n)), originalsize));

        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::move(op), std::move(init), *first);
        }
        return {std::move(init), first};
    }

}
















#endif //ALGOFUN_ACCUMULATE_N_HPP

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



    // FIXME: test this; std::indirect_binary_predicate<T*,std::projected<std::ranges::iterator_t<Range>, Proj>
    template<std::ranges::input_range Range, unsignedInt Size, typename T, class Proj=std::identity,
             std::predicate<T, typename std::projected<std::ranges::iterator_t<Range>, Proj>::value_type> BinaryOp>
    constexpr auto accumulate_n(Range&& range, Size&& n, T&& init, BinaryOp&& op, Proj&& proj={} )-> std::pair<T, std::ranges::iterator_t<Range>>
    {
        auto first = std::ranges::begin(range);
        if(n==0) return {std::forward<T>(init), first};

        //
        n =static_cast<unsigned >(std::min(static_cast<unsigned long long>(n), std::ranges::size(range)));
        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), std::invoke(proj, *first));
        }

        return {std::forward<T>(init), first};
    }

    // FIXME: add last iterator to avoid  !!
    template<std::input_iterator InputIt, std::unsigned_integral Size, typename T, std::predicate<T, std::iter_value_t<InputIt>> BinaryOp>
    constexpr auto accumulate_n(InputIt&& first,Size&& n, T&& init, BinaryOp&& op )-> std::pair<T, InputIt>
    {
        if(n==0) return {std::forward<T>(init), first};

        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), *first);
        }
        return {std::forward<T>(init), first};
    }

}
















#endif //ALGOFUN_ACCUMULATE_N_HPP

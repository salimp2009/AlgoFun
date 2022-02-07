//
// Created by salim on 03/02/2022.
//

#ifndef ALGOFUN_ACCUMULATE_N_HPP
#define ALGOFUN_ACCUMULATE_N_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{

    template<typename T>
    concept unsignedType = std::is_unsigned_v<T>;

    /// @warning    chrono::duration is not convertible to bool therefore  std::predicate<T, U> won't work
    /// @warning    therefore switched from std::predicate to std::regular_invocable
    static_assert(not std::convertible_to<std::chrono::duration<int>, bool>);
    static_assert(std::convertible_to<decltype(std::declval<std::chrono::duration<int>>().count()), bool>);


    template<std::ranges::input_range Range, unsignedType Size, typename T, class Proj=std::identity,
            std::regular_invocable<T, typename std::projected<std::ranges::iterator_t<Range>, Proj>::value_type> BinaryOp=std::plus<>>
    inline constexpr auto accumulate_n(Range&& range, Size&& n, T&& init=T{}, BinaryOp op={}, Proj&& proj={} )-> std::pair<T, std::ranges::iterator_t<Range>>
    {
        auto first = std::ranges::begin(range);
        if(n==0) return {std::forward<T>(init), first};

        const auto newLast = std::ranges::next(std::ranges::begin(range), n);
        const auto newSize = std::ranges::distance(std::ranges::begin(range), newLast);
        n =static_cast<Size>(std::ranges::min(newSize, std::ranges::ssize(range)));

        for(; n>0; --n, ++first)
        {
            init =std::invoke(std::forward<BinaryOp>(op), std::forward<T>(init), std::invoke(proj, *first));
        }

        return {std::forward<T>(init), first};
    }


    template<std::input_iterator InputIt, unsignedType Size, typename T=std::iter_value_t<InputIt> ,
            std::regular_invocable<T, std::iter_value_t<InputIt>> BinaryOp=std::plus<>>
    inline constexpr auto accumulate_n(InputIt first, InputIt last, Size&& n, T init=T{}, BinaryOp op={})-> std::pair<T, InputIt>
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



} // end of namespace

#endif //ALGOFUN_ACCUMULATE_N_HPP

//
// Created by salim on 15/01/2022.
//

#ifndef ALGOFUN_SLIDEALGORITHM_HPP
#define ALGOFUN_SLIDEALGORITHM_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{
    // FIXME: add another overload to cover the whole range first, selection as first/last and  position
    template<std::ranges::forward_range R>
    requires std::permutable<std::ranges::iterator_t<R>>
    constexpr std::ranges::subrange<std::ranges::iterator_t<R>> slide(R&& range,  std::ranges::iterator_t<R> position)
    {
        const auto first =std::ranges::begin(range);
        const auto last = std::ranges::end(range);

        if(position < first)    return  { std::ranges::rotate(position, first, last) };
        if(last < position)     return  { std::ranges::rotate(first, last, position) };
        return {first, last};
    }

    template<std::forward_iterator It>
    constexpr std::pair<It,It> slide(It first, It last, It position)
    {
        if (position < first)   return  { position, std::rotate(position, first, last) };
        if (last < position)    return  { std::rotate(first, last, position), position };
        return {first, last};
    }

    template<std::forward_iterator It>
    constexpr std::pair<It,It> slide_right(It first, It last, std::unsigned_integral auto number)
    {
            const auto position =std::next(last, number);
            return  { std::rotate(first, last, position), position };
    }

    template<std::bidirectional_iterator It>
    constexpr std::pair<It,It> slide_left(It first, It last,std::unsigned_integral auto number)
    {
        const auto position = std::prev(first, number);
        return  { position, std::rotate(position, first, last) };
    }


} // end of namespace
#endif //ALGOFUN_SLIDEALGORITHM_HPP

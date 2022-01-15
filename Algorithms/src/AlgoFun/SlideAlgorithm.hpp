//
// Created by salim on 15/01/2022.
//

#ifndef ALGOFUN_SLIDEALGORITHM_HPP
#define ALGOFUN_SLIDEALGORITHM_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{
    // FIXME: experimental; cant decide if the R should cover the whole range first , middle and position or
    // FIXME: just the selected part not including position


    template<std::ranges::forward_range R>
    requires std::permutable<std::ranges::iterator_t<R>>
    constexpr std::ranges::borrowed_subrange_t<R> slide(R&& range,  std::ranges::iterator_t<R> position)
    {
        auto first =std::ranges::begin(range);
        auto last = std::ranges::end(range);

        if(position < first)    return  { position, std::ranges::rotate(position, first, last) };
        if(last < position)     return  { std::ranges::rotate(first, last, position), position };
        return {first, last};
    }

    template<std::forward_iterator It>
    constexpr std::pair<It,It> slide(It first, It last, It position)
    {
        if(position < first)    return  { position, std::rotate(position, first, last) };
        if(last < position)     return  { std::rotate(first, last, position), position };
        return {first, last};
    }


} // end of namespace
#endif //ALGOFUN_SLIDEALGORITHM_HPP

//
// Created by salim on 15/01/2022.
//

#ifndef ALGOFUN_SLIDEALGORITHM_HPP
#define ALGOFUN_SLIDEALGORITHM_HPP

#include "algorithmsPCH.hpp"


namespace metafun
{
    template<std::permutable It, std::sentinel_for<It> S>
    constexpr std::ranges::subrange<It> slide(It first, It last,  S position)
    {
        if(position < first) return {position, std::ranges::rotate(position, first, last)};
        if(last < position) return{std::ranges::rotate(first, last, position), position};
        // if first< position <last
        return {first, last};
    }

    template<std::forward_iterator It>
    constexpr std::pair<It,It> slide(It first, It last, It position)
    {
        if(position < first) return {position, std::rotate(position, first, last)};
        if(last < position) return{std::rotate(first, last, position), position};
        // if first< position <last
        return {first, last};
    }


} // end of namespace
#endif //ALGOFUN_SLIDEALGORITHM_HPP

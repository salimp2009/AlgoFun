//
// Created by salim on 21/01/2022.
//

#ifndef ALGOFUN_SORTSUBRANGE_HPP
#define ALGOFUN_SORTSUBRANGE_HPP

#include "../algorithmsPCH.hpp"

namespace algofun {

    // FIXME::add some doxygen
    template<std::random_access_iterator It>
    constexpr void sortSubrange(It first, It last, It subfirst, It sublast) {
        if (subfirst == sublast) return;
        if (subfirst != sublast) {
            std::nth_element(first, subfirst, last);
            std::next(subfirst);
        }

        std::partial_sort(subfirst, sublast, last);
    }


    template<std::ranges::random_access_range R, class Comp = std::ranges::less, class Proj = std::identity>
        requires std::sortable<std::ranges::iterator_t<R>, Comp, Proj>
    constexpr void sortSubrange(R &&range, R &&subrange, Comp comp = {}, Proj proj = {}) {
        if (std::ranges::begin(subrange) == std::ranges::end(subrange)) return;
        if (std::ranges::begin(subrange) != std::ranges::end(subrange)) {
            std::ranges::nth_element(std::ranges::begin(range), std::ranges::begin(subrange), std::ranges::end(range), comp, proj);
            std::ranges::next(std::ranges::begin(subrange));
        }

        std::ranges::partial_sort(std::ranges::begin(subrange), std::ranges::end(subrange), std::ranges::end(range), comp, proj);
    }
}// namespace algofun

#endif//ALGOFUN_SORTSUBRANGE_HPP

//
// Created by salim on 21/01/2022.
//

#ifndef ALGOFUN_SORTSUBRANGE_HPP
#define ALGOFUN_SORTSUBRANGE_HPP

#include "algorithmsPCH.hpp"

namespace algofun
{

    // FIXME: add ranges version and also add some doxygen
    template<std::random_access_iterator It>
    constexpr void sortSubrange(It first, It last, It subfirst, It sublast)
    {
       if(subfirst==sublast) return;
       if(subfirst!=sublast)
       {
           std::nth_element(first, subfirst, last);
           std::next(subfirst);
       }

       std::partial_sort(subfirst, sublast, last);
    }

}

#endif //ALGOFUN_SORTSUBRANGE_HPP

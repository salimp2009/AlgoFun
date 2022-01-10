//
// Created by salim on 10/01/2022.
//

#ifndef ALGOFUN_ALGOFINDMISSINGELEM_HPP
#define ALGOFUN_ALGOFINDMISSINGELEM_HPP

#include "algorithmsPCH.hpp"

namespace algofun
{
    // changed unsigned* to Iterator, make the function generic and non-recursive; iterative
    // use concepts for the iterator type; Forward iterator and use STL iterator helper function
    // instead of pointer arithmetic

     auto find_missing_element(unsigned* first, unsigned* last, unsigned value =0)
    {
        if(first == last)
        {
            return value;
        }
        unsigned half =(last - first +1 ) / 2;
        unsigned m = half + value;
        auto p = std::partition(first, last, [&](auto elem) { return elem < m;} );
        if( p == first + half)
        {
            return find_missing_element(p, last, m);
        }
        else
        {
            return find_missing_element(first, p , value);
        }
    }




}

#endif //ALGOFUN_ALGOFINDMISSINGELEM_HPP

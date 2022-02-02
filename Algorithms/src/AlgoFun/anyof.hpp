//
// Created by salim on 02/02/2022.
//

#ifndef ALGOFUN_ANYOF_HPP
#define ALGOFUN_ANYOF_HPP

#include "algorithmsPCH.hpp"


namespace algofun
{
// FIXME : this is not working when it is in the test function but
//  any_of2 works when called from the main directly
    template<class I, class P>
    constexpr auto any_of2(I f, I l, P p)
    {
        return std::reduce(f, l, false,
                           [p](auto a, auto b) { return a || p(b); });
    }


} // endof namespace


#endif //ALGOFUN_ANYOF_HPP

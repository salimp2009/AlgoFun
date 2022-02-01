//
// Created by salim on 01/02/2022.
//

#ifndef ALGOFUN_ANYOFFAST_HPP
#define ALGOFUN_ANYOFFAST_HPP

#include "algorithmsPCH.hpp"

#endif //ALGOFUN_ANYOFFAST_HPP


namespace algofun
{
//<std::projected<I,Proj>> Pred >
    template<std::input_iterator I, std::sentinel_for<I> S,
            class Proj=std::identity, typename Pred>
    inline constexpr auto anyofFast(I&& First, S&& Last, Pred&& pred, Proj&& proj={})
    {
        return std::reduce(First, Last, false, [pred](auto& elem1, auto& elem2)
                                           {
                                                return elem1 || pred(elem2);
                                           } );
    }

    template<class I, class P>
    auto any_of2(I f, I l, P p) {
        return std::reduce(f, l, false,
                           [p](auto a, auto b) { return a || p(b); });
    }




} // end of namespace
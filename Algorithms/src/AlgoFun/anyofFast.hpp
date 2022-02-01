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
            class Proj=std::identity,
            std::indirect_binary_predicate<std::projected<I,Proj>, std::projected<S,Proj>> Pred>
    inline constexpr auto anyofFast(I&& First, S&& Last, Pred&& pred, Proj&& proj={}) ->std::pair<bool, I>
    {

        return std::reduce(First, Last, false, [&pred, &proj](const auto& elem1, const auto& elem2)
                                           {
                                                return proj(elem1) || pred(proj(elem2));
                                           } );

        return std::pair{true, First};
    }






} // end of namespace
//
// Created by salim on 13/02/2022.
//

#ifndef ALGOFUN_ALGOCONCEPTS_HPP
#define ALGOFUN_ALGOCONCEPTS_HPP

namespace algofun
{
    template<typename T>
    concept unsignedType = std::is_unsigned_v<T>;

    // FIXME: add a range version of this
    template<class T , class I ,class Op>
    concept indirectlyLeftFoldable =
            std::copy_constructible<Op> &&
            std::movable<T> &&
            std::indirectly_readable<I> &&
            std::invocable<Op, T, std::iter_reference_t<I>> &&
            std::assignable_from<T&, std::invoke_result_t<Op&, T, std::iter_reference_t<I>>>;

} // endof namespace algofun


#endif //ALGOFUN_ALGOCONCEPTS_HPP

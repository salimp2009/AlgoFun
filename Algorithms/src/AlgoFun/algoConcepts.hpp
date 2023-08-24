//
// Created by salim on 13/02/2022.
//

#ifndef ALGOFUN_ALGOCONCEPTS_HPP
#define ALGOFUN_ALGOCONCEPTS_HPP

#include "../algorithmsPCH.hpp"
namespace algofun::details {
    template<typename T>
    concept unsignedType = std::is_unsigned_v<T>;


    template<class Op, class T, class I, class RawResult,
             class DecayedResult = std::remove_cvref_t<RawResult>>
    concept indirectlyLeftFoldable_impl =
            std::convertible_to<T, DecayedResult> &&
            std::convertible_to<RawResult, DecayedResult> &&
            std::movable<DecayedResult> &&
            std::invocable<Op, DecayedResult, std::iter_reference_t<I>> &&
            std::assignable_from<DecayedResult &, std::invoke_result_t<Op &, DecayedResult, std::iter_reference_t<I>>>;


    template<class Op, class T, class I>
    concept indirectlyLeftFoldable =
            std::copy_constructible<Op> &&
            std::movable<T> &&
            std::indirectly_readable<I> &&
            std::invocable<Op, T, std::iter_reference_t<I>> &&
            indirectlyLeftFoldable_impl<Op, T, I, std::invoke_result_t<Op, T, std::iter_reference_t<I>>>;


    template<class R, class Op, class T, class U>
    concept binaryOperation =
            std::regular_invocable<Op, T, U> &&
            std::constructible_from<R, std::invoke_result_t<Op &, T, U>> &&
            std::assignable_from<R &, std::invoke_result_t<Op &, T, U>>;

    template<class R, class Op, class T, class U>
    concept magma =
            binaryOperation<R, Op, T, T> && binaryOperation<R, Op, U, U> &&
            binaryOperation<R, Op, T, U> && binaryOperation<R, Op, U, T>;


}// namespace algofun::details

namespace algofun {
    template<class R, class Op, class T, class U>
    concept semigroup =
            details::magma<R, Op, T, U> &&
            details::magma<R, Op, T, std::invoke_result_t<Op &, T, U>> &&
            details::magma<R, Op, std::invoke_result_t<Op &, T, U>, U>;

}// end of namespace algofun


#endif//ALGOFUN_ALGOCONCEPTS_HPP

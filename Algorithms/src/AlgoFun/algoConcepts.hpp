//
// Created by salim on 13/02/2022.
//

#ifndef ALGOFUN_ALGOCONCEPTS_HPP
#define ALGOFUN_ALGOCONCEPTS_HPP

namespace algofun::details
{
    template<typename T>
    concept unsignedType = std::is_unsigned_v<T>;


    template<class Op, class T , class I, class RawResult,
            class DecayedResult = std::remove_cvref_t<RawResult>>
    concept indirectlyLeftFoldable_impl =
            std::convertible_to<T, DecayedResult> &&
            std::convertible_to<RawResult, DecayedResult> &&
            std::movable<DecayedResult> &&
            std::invocable<Op, DecayedResult, std::iter_reference_t<I>> &&
            std::assignable_from<DecayedResult&, std::invoke_result_t<Op&, DecayedResult, std::iter_reference_t<I>>>;


    template<class Op, class T , class I >
    concept indirectlyLeftFoldable =
            std::copy_constructible<Op> &&
            std::movable<T> &&
            std::indirectly_readable<I> &&
            std::invocable<Op, T, std::iter_reference_t<I>> &&
            //std::assignable_from<T&, std::invoke_result_t<Op&, T, std::iter_reference_t<I>>>;
            indirectlyLeftFoldable_impl<Op, T, I, std::invoke_result_t<Op, T, std::iter_reference_t<I>>>;

} // endof namespace algofun


#endif //ALGOFUN_ALGOCONCEPTS_HPP

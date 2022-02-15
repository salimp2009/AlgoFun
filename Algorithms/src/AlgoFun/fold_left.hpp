//
// Created by salim on 15/02/2022.
//

#ifndef ALGOFUN_FOLD_LEFT_HPP
#define ALGOFUN_FOLD_LEFT_HPP

namespace algofun
{
    // FIXME: add a range version and
    //  update the concept details::indirectlyLeftFoldable for projection
    template<std::input_iterator I, std::sentinel_for<I> S, class T,
            details::indirectlyLeftFoldable<T, I> Op>
    auto constexpr fold_left(I first, S last, T&& init, Op op)
    {
        using R = std::invoke_result_t<Op&, T, std::iter_reference_t<I>>;
        if(first == last)
        {
            return R(std::forward<T>(init));
        }

        auto accum = std::invoke(op, std::forward<T>(init), *first);
        for(++first; first != last; ++first)
        {
          accum = std::invoke(op, std::forward<decltype(accum)>(accum), *first);
        }

        return accum;
    }









} // end of namespace





#endif //ALGOFUN_FOLD_LEFT_HPP

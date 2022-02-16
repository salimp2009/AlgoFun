//
// Created by salim on 15/02/2022.
//

#ifndef ALGOFUN_STABLE_PARTITIONPOS_HPP
#define ALGOFUN_STABLE_PARTITIONPOS_HPP


// FIXME: Delete file; This is only for learning stable_partition from GCCs implementation
namespace algofun::details
{
//
//
//    template<typename Pred, typename Proj>
//    constexpr auto
//    __make_pred_proj(Pred& pred, Proj& proj)
//    {
//        return [&] <typename Tp> (Tp&& arg) -> bool {
//            return std::invoke(pred,
//                                 std::invoke(proj, std::forward<Tp>(arg)));
//        };
//    }




} // end of namespace algofun::details


namespace algofun
{

//    template<typename _ForwardIterator, typename _Pointer, typename _Predicate,
//             typename _Distance>
//    _ForwardIterator
//    __stable_partition_adaptive(_ForwardIterator __first,
//                                _ForwardIterator __last,
//                                _Predicate __pred, _Distance __len,
//                                _Pointer __buffer,
//                                _Distance __buffer_size)
//    {
//        if (__len == 1)
//            return __first;
//
//        if (__len <= __buffer_size)
//        {
//            _ForwardIterator __result1 = __first;
//            _Pointer __result2 = __buffer;
//
//            // The precondition guarantees that !__pred(__first), so
//            // move that element to the buffer before starting the loop.
//            // This ensures that we only call __pred once per element.
//            *__result2 = _GLIBCXX_MOVE(*__first);
//            ++__result2;
//            ++__first;
//            for (; __first != __last; ++__first)
//                if (__pred(__first))
//                {
//                    *__result1 = _GLIBCXX_MOVE(*__first);
//                    ++__result1;
//                }
//                else
//                {
//                    *__result2 = _GLIBCXX_MOVE(*__first);
//                    ++__result2;
//                }
//
//            _GLIBCXX_MOVE3(__buffer, __result2, __result1);
//            return __result1;
//        }
//
//        _ForwardIterator __middle = __first;
//        std::advance(__middle, __len / 2);
//        _ForwardIterator __left_split =
//                std::__stable_partition_adaptive(__first, __middle, __pred,
//                                                 __len / 2, __buffer,
//                                                 __buffer_size);
//
//        // Advance past true-predicate values to satisfy this
//        // function's preconditions.
//        _Distance __right_len = __len - __len / 2;
//        _ForwardIterator __right_split =
//                std::__find_if_not_n(__middle, __right_len, __pred);
//
//        if (__right_len)
//            __right_split =
//                    std::__stable_partition_adaptive(__right_split, __last, __pred,
//                                                     __right_len,
//                                                     __buffer, __buffer_size);
//
//        return std::rotate(__left_split, __middle, __right_split);
//    }

//    template<typename _ForwardIterator, typename _Predicate>
//    _ForwardIterator
//    __stable_partition(_ForwardIterator __first, _ForwardIterator __last,
//                       _Predicate __pred)
//    {
//        __first = std::__find_if_not(__first, __last, __pred);
//
//        if (__first == __last)
//            return __first;
//
//        typedef typename iterator_traits<_ForwardIterator>::value_type
//                _ValueType;
//        typedef typename iterator_traits<_ForwardIterator>::difference_type
//                _DistanceType;
//
//        _Temporary_buffer<_ForwardIterator, _ValueType>
//                __buf(__first, std::distance(__first, __last));
//        return
//                std::__stable_partition_adaptive(__first, __last, __pred,
//                                                 _DistanceType(__buf.requested_size()),
//                                                 __buf.begin(),
//                                                 _DistanceType(__buf.size()));
//    }




//    template<typename _ForwardIterator, typename _Predicate>
//    inline _ForwardIterator
//    stable_partition(_ForwardIterator __first, _ForwardIterator __last,
//                     _Predicate __pred)
//    {
//        // concept requirements
//        __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
//                                    _ForwardIterator>)
//                __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
//                                                                   typename iterator_traits<_ForwardIterator>::value_type>)
//                        __glibcxx_requires_valid_range(__first, __last);
//
//        return stable_partition(__first, __last,
//                                       __gnu_cxx::__ops::__pred_iter(__pred));
//    }


    //struct __stable_partition_fn
    //{
        //    template<std::bidirectional_iterator _Iter, std::sentinel_for<_Iter> _Sent,
        //             typename _Proj = std::identity,
        //             std::indirect_unary_predicate<std::projected<_Iter, _Proj>> _Pred>
        //    requires std::permutable<_Iter>
        //            std::ranges::subrange<_Iter>
        //    operator()(_Iter __first, _Sent __last,
        //               _Pred __pred, _Proj __proj = {}) const
        //    {
        //        auto __lasti = std::ranges::next(__first, __last);
        //        auto __middle
        //                = stable_partition(std::move(__first), __lasti,
        //                                        __detail::__make_pred_proj(__pred, __proj));
        //        return {std::move(__middle), std::move(__lasti)};
        //    }
        //
        //    template<std::ranges::bidirectional_range _Range, typename _Proj = std::identity,
        //             std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<_Range>, _Proj>>
        //                     _Pred>
        //    requires permutable<std::ranges::iterator_t<_Range>>
        //            borrowed_subrange_t<_Range>
        //    operator()(_Range&& __r, _Pred __pred, _Proj __proj = {}) const
        //    {
        //        return (*this)(ranges::begin(__r), ranges::end(__r),
        //                       std::move(__pred), std::move(__proj));
        //    }
    //};

    //inline constexpr __stable_partition_fn stable_partition{};

} // end of namespace



#endif//ALGOFUN_STABLE_PARTITIONPOS_HPP

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

//    template<typename InputIterator, typename Predicate, typename Distance>
//    constexpr InputIterator
//    find_if_not_nSP(InputIterator first, Distance& len, Predicate pred)
//    {
//        for (; len; --len,  (void) ++first)
//            if (!__pred(first))
//                break;
//        return first;
//    }
//
//    template<typename ForwardIterator, typename Pointer, typename Predicate,
//             typename Distance>
//    ForwardIterator
//    stable_partition_adaptiveSP(ForwardIterator first,
//                                ForwardIterator last,
//                                Predicate pred, Distance len,
//                                Pointer buffer,
//                                Distance bufferSize)
//    {
//        if (len == 1)
//            return first;
//
//        if (len <= bufferSize)
//        {
//            ForwardIterator result1 = first;
//            Pointer result2 = buffer;
//
//            // The precondition guarantees that !pred(first), so
//            // move that element to the buffer before starting the loop.
//            // This ensures that we only call pred once per element.
//            *result2 = std::move(*first);
//            ++result2;
//            ++first;
//            for (; first != last; ++first)
//                if (pred(first))
//                {
//                    *result1 = std::move(*first);
//                    ++result1;
//                }
//                else
//                {
//                    *result2 = std::move(*first);
//                    ++result2;
//                }
//
//            std::move(buffer, result2, result1);
//            return result1;
//        }
//
//        ForwardIterator middle = first;
//        std::advance(middle, len / 2);
//        ForwardIterator leftSplit =
//                stable_partition_adaptiveSP(first, middle, pred,
//                                                 len / 2, buffer,
//                                                 bufferSize);
//
//        // Advance past true-predicate values to satisfy this
//        // function's preconditions.
//        Distance rightLen = len - len / 2;
//        ForwardIterator rightSplit =
//
//                find_if_not_nSP(middle, rightLen, pred);
//
//        if (rightLen)
//            rightSplit =
//                    std::__stable_partition_adaptive(rightSplit, last, pred,
//                                                     rightLen,
//                                                     buffer, bufferSize);
//
//        return std::rotate(leftSplit, middle, rightSplit);
//    }
//
//    template<typename ForwardIterator, typename Predicate>
//    ForwardIterator
//    stable_partitionSP(ForwardIterator first, ForwardIterator last,
//                       Predicate pred)
//    {
//        first = std::ranges::find_if_not(first, last, pred);
//
//        if (first == last)
//            return first;
//        std::stable_partition()
//
//        typedef typename std::iterator_traits<ForwardIterator>::value_type
//                value_type;
//        typedef typename std::iterator_traits<ForwardIterator>::difference_type
//                distanceType;
//
//        _Temporary_buffer<ForwardIterator, value_type>
//                buf(first, std::distance(first, last));
//        return
//                stable_partition_adaptiveSP(first, last, pred,
//                                           distanceType(buf.requested_size()),
//                                           buf.begin(),
//                                           distanceType(buf.size()));
//    }



//    struct stable_partition_SP
//    {
//            template<std::bidirectional_iterator It, std::sentinel_for<It> Sent,
//                     typename Proj = std::identity,
//                     std::indirect_unary_predicate<std::projected<It, Proj>> Pred>
//            requires std::permutable<It>
//                    std::ranges::subrange<It>
//            operator()(It first, Sent last,
//                       Pred pred, Proj proj = {}) const
//            {
//                auto lasti = std::ranges::next(first, last);
//                auto middle = stable_partitionSP(std::move(first), lasti,
//                                                std::invoke(pred, proj));
//                return {std::move(middle), std::move(lasti)};
//            }

//            template<std::ranges::bidirectional_range _Range, typename _Proj = std::identity,
//                     std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<_Range>, _Proj>>
//                             _Pred>
//            requires std::permutable<std::ranges::iterator_t<_Range>>
//                    borrowed_subrange_t<_Range>
//            operator()(_Range&& __r, _Pred __pred, _Proj __proj = {}) const
//            {
//                return (*this)(std::ranges::begin(__r), std::ranges::end(__r),
//                               std::move(__pred), std::move(__proj));
//            }
 //   };

//    inline constexpr stable_partition_SP stable_partition{};




} // end of namespace



#endif//ALGOFUN_STABLE_PARTITIONPOS_HPP

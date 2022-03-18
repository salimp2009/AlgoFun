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

    template<std::input_iterator InputIterator, typename Proj, typename Predicate, typename Distance>

    constexpr auto  find_if_not_nSP(InputIterator first, Distance& len, Predicate pred, Proj proj) ->InputIterator
    {
        for (; len; --len,  (void) ++first)
            if (!std::invoke(pred, std::invoke(proj, first)))
                break;
        return first;
    }

    template<std::forward_iterator ForwardIterator, typename Pointer, typename Proj, typename Predicate, typename Distance>
    constexpr auto stablePartitionAdaptiveSp(ForwardIterator first, ForwardIterator last, Predicate pred, Proj proj,
                                             Distance len, Pointer buffer, Distance bufferSize) ->ForwardIterator
    {
        if (len == 1) return first;

        if (len <= bufferSize)
        {
            ForwardIterator result1 = first;
            Pointer result2 = buffer;

            // The precondition guarantees that !pred(first), so
            // move that element to the buffer before starting the loop.
            // This ensures that we only call pred once per element.
            *result2 = std::move(*first);
            ++result2;
            ++first;
            for (; first != last; ++first)
                if (std::invoke(pred, std::invoke(proj, first)))
                {
                    *result1 = std::move(*first);
                    ++result1;
                }
                else
                {
                    *result2 = std::move(*first);
                    ++result2;
                }

            std::move(buffer, result2, result1);
            return result1;
        }

        ForwardIterator middle = first;
        std::advance(middle, len / 2);
        ForwardIterator leftSplit = stablePartitionAdaptiveSp(first, middle, pred, proj, len / 2, buffer, bufferSize);

        // Advance past true-predicate values to satisfy this
        // function's preconditions.
        Distance rightLen = len - len / 2;
        ForwardIterator rightSplit = find_if_not_nSP(middle, rightLen, pred, proj);

        if (rightLen)
        {
            rightSplit = stablePartitionAdaptiveSp(rightSplit, last, pred,proj, rightLen, buffer, bufferSize);
        }

        return std::rotate(leftSplit, middle, rightSplit);
    }

    template<std::forward_iterator ForwardIterator, typename Proj = std::identity,
            std::indirect_unary_predicate<std::projected<ForwardIterator, Proj>> Pred>
    constexpr auto stablePartitionSp(ForwardIterator first, ForwardIterator last, Pred pred, Proj proj={}) ->ForwardIterator
    {
        first = std::ranges::find_if_not(first, last, pred, proj);

        if (first == last) { return first; }

        using distanceType = typename std::iterator_traits<ForwardIterator>::difference_type;

        std::array<std::iter_value_t<ForwardIterator>, std::distance(first, last)> buf;
        return stablePartitionAdaptiveSp(first, last, pred, proj,
                                         distanceType(std::size(buf)),
                                         std::begin(buf),
                                         distanceType(std::size(buf)));
    }


    struct stable_partitionSP
    {
            template<std::bidirectional_iterator It, std::sentinel_for<It> Sent, typename Proj = std::identity,
                     std::indirect_unary_predicate<std::projected<It, Proj>> Pred>
            requires std::permutable<It>
            constexpr auto  operator()(It first, Sent last, Pred pred, Proj proj = {}) const ->std::ranges::subrange<It>
            {
                auto lasti = std::ranges::next(first, last);
                auto middle = stablePartitionSp(std::move(first), lasti, std::move(pred), std::move(proj));
                return {std::move(middle), std::move(lasti)};
            }


            template<std::ranges::bidirectional_range Range, typename Proj = std::identity,
                     std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<Range>, Proj>> Pred>
            requires std::permutable<std::ranges::iterator_t<Range>>

            constexpr auto operator()(Range &&r, Pred pred, Proj proj = {}) const ->std::ranges::borrowed_subrange_t<Range>
            {
                return (*this)(std::ranges::begin(r), std::ranges::end(r), std::move(pred), std::move(proj));
            }
    };

    inline constexpr stable_partitionSP stable_partition{};




} // end of namespace



#endif//ALGOFUN_STABLE_PARTITIONPOS_HPP

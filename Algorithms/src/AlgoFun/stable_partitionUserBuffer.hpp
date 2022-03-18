//
// Created by salim on 18/03/2022.
//

#ifndef ALGOFUN_STABLE_PARTITIONUSERBUFFER_HPP
#define ALGOFUN_STABLE_PARTITIONUSERBUFFER_HPP


// FIXME: This is only for learning stable_partition from GCCs implementation
//  converted to use as stable_partitionPosition; similar one used for stablePartionBuffer

namespace algofun
{

    template<std::input_iterator InputIterator, typename Proj, typename Predicate, typename Distance>

    constexpr auto  find_if_not_nBuff(InputIterator first, Distance& len, Predicate pred, Proj proj) ->InputIterator
    {
        for (; len; --len,  (void) ++first)
            if (!std::invoke(pred, std::invoke(proj, *first)))
                break;
        return first;
    }

    template<std::forward_iterator ForwardIterator, typename Pointer, typename Proj, typename Predicate, typename Distance>
    constexpr auto stablePartitionAdaptiveBuff(ForwardIterator first, ForwardIterator last, Predicate pred, Proj proj,
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
                if (std::invoke(pred, std::invoke(proj, *first)))
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
        ForwardIterator leftSplit = stablePartitionAdaptiveBuff(first, middle, pred, proj, len / 2, buffer, bufferSize);

        // Advance past true-predicate values to satisfy this
        // function's preconditions.
        Distance rightLen = len - len / 2;
        ForwardIterator rightSplit = find_if_not_nBuff(middle, rightLen, pred, proj);

        if (rightLen)
        {
            rightSplit = stablePartitionAdaptiveBuff(rightSplit, last, pred,proj, rightLen, buffer, bufferSize);
        }

        return std::rotate(leftSplit, middle, rightSplit);
    }

    template<std::forward_iterator ForwardIterator, typename Proj = std::identity,
             std::indirect_unary_predicate<std::projected<ForwardIterator, Proj>> Pred>
    constexpr auto stable_partitionBuff(ForwardIterator first, ForwardIterator last, Pred pred, Proj proj={}) ->ForwardIterator
    {
        first = std::ranges::find_if_not(first, last, pred, proj);

        if (first == last) { return first; }

        using distanceType = typename std::iterator_traits<ForwardIterator>::difference_type;

        // FIXME: this is temporary; we will use the buffer passed by User
        std::array<std::iter_value_t<ForwardIterator>, std::distance(first, last)> buf;
        auto requestedSize = std::distance(first, last);
        return stablePartitionAdaptiveBuff(first, last, pred, proj,
                                         distanceType(requestedSize),
                                         std::begin(buf),
                                         distanceType(std::size(buf)));
    }


    struct stable_partitionBuffer {
        template<std::bidirectional_iterator It, std::sentinel_for<It> Sent, typename Proj = std::identity,
                 std::indirect_unary_predicate<std::projected<It, Proj>> Pred>
        requires std::permutable<It>
        constexpr auto  operator()(It first, Sent last, Pred pred, Proj proj = {}) const ->std::ranges::subrange<It>
        {
            auto lasti = std::ranges::next(first, last);
            auto middle = stable_partitionBuff(std::move(first), lasti, std::move(pred), std::move(proj));
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

    inline constexpr stable_partitionBuffer stable_partitionBuffer{};




} // end of namespace

#endif//ALGOFUN_STABLE_PARTITIONUSERBUFFER_HPP

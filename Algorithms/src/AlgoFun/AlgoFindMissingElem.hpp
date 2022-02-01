//
// Created by salim on 10/01/2022.
//

#ifndef ALGOFUN_ALGOFINDMISSINGELEM_HPP
    #include "algorithmsPCH.hpp"
#define ALGOFUN_ALGOFINDMISSINGELEM_HPP



namespace algofun
{

    // linear time; n+n/2 +n/4..
    // in place
    // although forward_iterator is used it also supports random access, bidirectional iterators as well
    // e.g: vectors, arrays, lists, forward iterators will work

    /* Contracts; pre-post conditions;
     * (Pre) [fist,las) does not contain all possible value (there are missing elems)
     * (Pre) last is reachable from first; using iterator helper functions
     * (Pre?) [first, last) no duplicate values of T; not sure if this is needed!!
     * (Pre?) value should Snot overflow if T is signed
     */

    /// @param  first   start iterator of a range/container
    /// @param  last    end of the iterator (it is one past the last value)
    /// @param  value   the start value of range; if not passed then default zero will be used
    /// @returns type T min absent value in the given range
    /// @complexity at most N applications;
    /// @swaps  at most N/2 swaps if I models ranges::bidirectional_iterator, and at most N swaps otherwise
    template<std::forward_iterator It, typename T=std::iter_value_t<It>>
    constexpr auto min_absent(It first, It last, T value=T{})
    {
      using diff_t = decltype(value-value);
      while(last!=first)
      {
          const auto half =(std::distance(first,last)+1)/ 2 ;
          const T m = static_cast<diff_t>(half) + value;
          const auto p = std::partition(first, last, [&](auto elem) { return elem < m;} );
          if ( p == std::next(first, half))
          {
             first = p;
             value = m;
          }
          else
          {
              last =p;
          }
      }
       return value;
    }

    // similar to original version but used std::nth_element instead std::partition;
    // this version is said to be slower;needs to be tested
    template<std::forward_iterator It, typename T=std::iter_value_t<It>>
    constexpr auto min_absent2(It first, It last, T value=T{})
    {
        using diff_t = decltype(value-value);
        while(first!=last)
        {
            const auto half =std::distance(first,last)/ 2 ;
            const auto mid =std::next(first, half);
            std::nth_element(first, mid, last);
            if ( *mid == value + static_cast<diff_t>(half))
            {
                value = *mid + static_cast<diff_t>(1);
                first = std::next(mid);
            }
            else
            {
                last =mid;
            }
        }
        return value;
    }




} // end of namespace

#endif //ALGOFUN_ALGOFINDMISSINGELEM_HPP

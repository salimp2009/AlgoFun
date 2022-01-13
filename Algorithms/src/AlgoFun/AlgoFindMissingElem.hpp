//
// Created by salim on 10/01/2022.
//

#ifndef ALGOFUN_ALGOFINDMISSINGELEM_HPP
#define ALGOFUN_ALGOFINDMISSINGELEM_HPP

#include "algorithmsPCH.hpp"

namespace algofun
{

    // linear time; n+n/2 +n/4..
    // in place
    // although forward_iterator is used it also supports random access, bi-directional iterators as well
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




} // end of namespace

#endif //ALGOFUN_ALGOFINDMISSINGELEM_HPP

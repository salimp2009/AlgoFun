//
// Created by salim on 10/01/2022.
//

#ifndef ALGOFUN_ALGOFINDMISSINGELEM_HPP
#define ALGOFUN_ALGOFINDMISSINGELEM_HPP

#include "algorithmsPCH.hpp"

namespace algofun
{

    // use STL iterator helper function; advance, next, distance...
    // instead of pointer arithmetics

    ///@ A:find_missing_element()
    ///@ linear time; n+n/2 +n/4..
    ///@ in place
    ///@ although forward_iterator is used it also supports random access, bi-directional iterators as well
    ///@ e.g: vectors, arrays, lists, forward iterators will work
    template<std::forward_iterator It, typename T=std::iter_value_t<It>>
     auto find_missing_element(It first, It last, T value=T{})
    {
      // added this instead of passing 1 as default to the value it works for numerical values
      // need to test for other types; if T{} is given then the search does not work
      // need to find a better way without this ???
      ++value;

      while(last!=first)
      {
          T half =(std::distance(first,last)+1 )/ 2 ;
          T m = half + value;
          auto p = std::partition(first, last, [&](auto elem) { return elem < m;} );
          if( p == std::next(first, half))
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

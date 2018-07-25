#ifndef __FUNCTIONAL_HPP__
#define __FUNCTIONAL_HPP__

#include <utility>
#include <vector>

template <typename T, typename Function >
auto map( Function&& fn, std::vector<T > const & xs ) -> std::vector<decltype(fn(std::declval<T>()))> {
    using ReturnType = decltype(fn(std::declval<T>()));
    std::vector<ReturnType> out;
    //out.resize( xs.size() );
    for ( auto&& x : xs ) {
        out.push_back( fn( x ) );
    }
    return out;
}


#endif // __FUNCTIONAL_HPP__

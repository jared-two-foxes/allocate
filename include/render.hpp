#ifndef RENDER_HPP__
#define RENDER_HPP___

#include <allocate/functional.hpp>
#include <allocate/string_helper.hpp>

#include <terminal/components/component.hpp>
#include <terminal/components/flowlayout.hpp>
#include <terminal/components/stacklayout.hpp>

#include <vector>
#include <utility>

namespace ui
{

template <typename T >
framework::Component render( const T& o )  {
    return framework::Text { cast( o ) };
}

template <typename T >
framework::Component render( const T& value, int w );

template <>
framework::Component render( const std::string& s, int w ) {
    std::string str( s );
    if ( str.length() > w ) {
        str = str.substr( 0, str.length() );
    }
    else if ( w > str.length() ) {
        str.append( w - str.length(), ' ' );
    }
    return framework::Text { str };
}

template <>
framework::Component render( const float& o, int w ) {
    return render( cast( o ), w );
}

template <typename T >
framework::Component render( const T& o, const std::string& delim ) {
    return render( cast( o ) + delim );
}

template <typename T >
framework::Component render( const T& o, int w, const std::string& delim ) {
    return render( cast( o ) + delim, w );
}

template <typename T, typename U>
framework::Component render( std::pair<T, U> const& pair ) {
    return render( pair.first, pair.second );
}

template <typename T, typename U>
framework::Component render( std::pair<T, U> const& pair, const std::string& delim ) {
    return render( pair.first, pair.second, delim );
}



template <typename Function, typename... Components >
framework::Component stack( Function fn, Components... c ) {
    return framework::StackLayout<> {
        fn( c )...,
    };
}

template <typename Function, typename... Components >
framework::Component flow( Function fn, Components... c ) {
    return framework::FlowLayout<> {
        fn( c )...,
    };
}

}

#endif // RENDER_HPP__

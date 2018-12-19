#ifndef RENDER_HPP__
#define RENDER_HPP___

#include <terminal/components/component.hpp>
#include <terminal/components/flowlayout.hpp>
#include <terminal/components/stacklayout.hpp>

#include <foundation/base/functional.hpp>
#include <foundation/strings/utils.hpp>

#include <vector>
#include <utility>

namespace ui
{

template <typename T >
framework::Component render( const T& o )  {
    return framework::Text { foundation::toString( o ) };
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
    return render( foundation::toString( o ), w );
}

template <typename T >
framework::Component render( const T& o, const std::string& delim ) {
    return render( foundation::toString( o ) + delim );
}

template <typename T >
framework::Component render( const T& o, int w, const std::string& delim ) {
    return render( foundation::toString( o ) + delim, w );
}

template <typename T, typename U>
framework::Component render( std::pair<T, U> const& pair ) {
    return render( pair.first, pair.second );
}

template <typename T, typename U>
framework::Component render( std::pair<T, U> const& pair, const std::string& delim ) {
    return render( pair.first, pair.second, delim );
}



template <typename... Components >
framework::Component stack( Components... c ) {
    return framework::StackLayout<> {
        render( c )...,
    };
}

template <typename... Components >
framework::Component flow( Components... c ) {
    return framework::FlowLayout<> {
        render( c )...,
    };
}

}

#endif // RENDER_HPP__

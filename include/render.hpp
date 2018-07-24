#ifndef RENDER_HPP__
#define RENDER_HPP___

#include <allocate/string_helper.hpp>

#include <framework/terminal/components/component.hpp>
#include <framework/terminal/components/flowlayout.hpp>
#include <framework/terminal/components/stacklayout.hpp>

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



template <typename T >
framework::Component render_stack( const std::vector<T >& items )
{
    framework::StackLayout<> stack {};
    for ( const auto& elem : items ) {
        stack.children.push_back( render( elem ) );
    }
    return stack;
}

template <typename T >
framework::Component render_flow( const std::vector<T >& items )
{
    framework::FlowLayout<> flow {};
    for ( const auto& elem : items ) {
        flow.children.push_back( render( elem ) );
    }
    return flow;
}

template <typename... Components >
framework::Component flow(std::string delim, Components... c) {
    return framework::FlowLayout<> {
        render(c, delim)...,
    };
}

}

#endif // RENDER_HPP__

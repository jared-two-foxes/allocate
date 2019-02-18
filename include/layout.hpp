#ifndef ALLOCATE_LAYOUT_HPP__
#define ALLOCATE_LAYOUT_HPP___

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
framework::Component render( T const & o ) {
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


template <typename... Elements >
framework::Component stack( Elements... el ) {
  return framework::StackLayout<> {
    render( el )...,
  };
}

template <typename... Elements >
framework::Component flow( Elements... el ) {
  return framework::FlowLayout<> {
    render( el )...,
  };
}

}

#endif // ALLOCATE_LAYOUT_HPP__

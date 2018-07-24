#ifndef STRING_HELPER_HPP__
#define STRING_HELPER_HPP__

#include <iomanip>
#include <sstream>
#include <string>

namespace ui
{

template <typename T >
std::string cast( T const& o );

std::string cast( float const& o ) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << o;
    return stream.str();
}

std::string cast( std::string const& o ) {
    return std::string( o );
}

}

#endif // string_helper

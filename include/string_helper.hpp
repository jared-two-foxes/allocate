#ifndef STRING_HELPER_HPP__
#define STRING_HELPER_HPP__

#include <iomanip>
#include <sstream>
#include <string>

namespace ui
{

template <typename T >

std::string cast( T const& o );
inline std::string cast( float const& o ) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << o;
    return stream.str();
}

inline std::string cast( std::string const& o ) {
    return std::string( o );
}




inline std::vector<std::string> split( std::string str, std::string token ) {
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}



}

#endif // string_helper

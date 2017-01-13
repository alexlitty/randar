#ifndef RANDAR_UTILITY_JSON_HPP
#define RANDAR_UTILITY_JSON_HPP

#include <string>
#include <randar/Utility/Awesomium.hpp>

namespace randar
{
    std::string toJson(const Awesomium::JSValue& value);
}

#endif

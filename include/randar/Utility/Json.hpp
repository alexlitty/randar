#ifndef RANDAR_UTILITY_JSON_HPP
#define RANDAR_UTILITY_JSON_HPP

#include <string>
#include <Awesomium/WebCore.h>

namespace randar
{
    std::string toJson(Awesomium::JSValue value);
}

#endif

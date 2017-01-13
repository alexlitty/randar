#include <randar/Utility/Js.hpp>

Awesomium::JSValue randar::toJs(const std::string& string)
{
    return Awesomium::JSValue(Awesomium::ToWebString(string));
}

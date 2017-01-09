#include <randar/Utility/Json.hpp>

std::string randar::toJson(Awesomium::JSValue value)
{
    std::string result;

    // JSON has no "undefined" value. Interpret as null.
    if (value.IsUndefined()) {
        result = "null";
    }

    // Awesomium doesn't have a stringifying method for objects. Use our own.
    else if (value.IsObject()) {
        Awesomium::JSObject object = value.ToObject();
        Awesomium::JSArray propertyNames = object.GetPropertyNames();
    }

    // Use Awesomium stringifying.
    else {
        char *str = nullptr;
        value.ToString().ToUTF8(str, 0);
        result = std::string(str);

        // Strings need to be wrapped in quotes.
        if (value.IsString()) {
            result = std::string("\"") + result + std::string("\"");
        }
    }

    return result;
}

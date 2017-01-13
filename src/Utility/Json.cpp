#include <randar/Utility/Json.hpp>

std::string randar::toJson(const Awesomium::JSValue& value)
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
        unsigned int propertyCount = propertyNames.size();

        result = "{";
        for (unsigned int i = 0; i < propertyCount; i++) {
            result += randar::toJson(propertyNames[i])
                    + ":"
                    + randar::toJson(object.GetProperty(propertyNames[i].ToString()));

            if (i != (propertyCount - 1)) {
                result += ",";
            }
        }
        result += "}";
    }

    // Use Awesomium stringifying.
    else {
        result = randar::toString(value.ToString());

        // Strings need to be wrapped in quotes.
        if (value.IsString()) {
            result = "\"" + result + "\"";
        }
    }

    return result;
}

#ifndef RADAPTER_UTILITY_PROPERTY_DESCRIPTOR_HPP
#define RADAPTER_UTILITY_PROPERTY_DESCRIPTOR_HPP

#include <radapter/Utility/Unwrap.hpp>

namespace radapter
{
    template <radapter::Callback T>
    napi_property_descriptor getter(const char* name)
    {
        return {
            name,
            0,

            0,
            radapter::unwrap::cb<T>,
            0,
            0,

            napi_default,
            0
        };
    }

    template <radapter::Callback T>
    napi_property_descriptor setter(const char* name)
    {
        return {
            name,
            0,

            0,
            0,
            radapter::unwrap::cb<T>,
            0,

            napi_default,
            0
        };
    }

    template <radapter::Callback T, radapter::Callback U>
    napi_property_descriptor getterSetter(const char* name)
    {
        return {
            name,
            0,

            0,
            radapter::unwrap::cb<T>,
            radapter::unwrap::cb<U>,
            0,

            napi_default,
            0
        };
    }

    template <radapter::Callback T>
    napi_property_descriptor methodProperty(const char* name)
    {
        return {
            name,
            0,

            radapter::unwrap::cb<T>,
            0,
            0,
            0,

            napi_default,
            0
        };
    }
}

#endif

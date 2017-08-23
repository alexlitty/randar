#ifndef RADAPTER_UTILITY_NATIVE_VALUE_HPP
#define RADAPTER_UTILITY_NATIVE_VALUE_HPP

#include <radapter/Utility/CheckNapi.hpp>

namespace radapter
{
    template <typename T>
    T nativeValue(napi_env env, napi_value value)
    {
        throw new std::runtime_error("Not implemented");
    }

    template <> float nativeValue(napi_env env, napi_value value);
    template <> double nativeValue(napi_env env, napi_value value);
}

#endif

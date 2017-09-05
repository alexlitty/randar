#ifndef RADAPTER_UTILITY_NAPI_VALUE_HPP
#define RADAPTER_UTILITY_NAPI_VALUE_HPP

#include <radapter/Utility/CheckNapi.hpp>

namespace radapter
{
    /*napi_value napiValue(napi_env env)
    {
        napi_value result;
        checkNapi("get napi undefined object", env, napi_get_undefined(
            env,
            &result
        ));
        return result;
    }*/

    template <typename T> napi_value napiValue(napi_env env, T value)
    {
        throw std::runtime_error("Conversion not implemented");
    }

    template <> napi_value napiValue(napi_env env, double value);
    template <> napi_value napiValue(napi_env env, float value);
}

#endif

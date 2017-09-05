#include <radapter/Utility/NapiValue.hpp>
#include <iostream>

namespace radapter
{
    // Empty value retrievers.
    napi_value napiUndefinedValue(napi_env env)
    {
        napi_value result;
        checkNapi("get napi undefined object", env, napi_get_undefined(
            env,
            &result
        ));
        return result;
    }

    napi_value napiNullValue(napi_env env)
    {
        napi_value result;
        checkNapi("get napi null object", env, napi_get_null(
            env,
            &result
        ));
        return result;
    }

    // Floating point specializations.
    template <> napi_value napiValue(napi_env env, float value)
    {
        return radapter::napiValue<double>(env, value);
    }

    template <> napi_value napiValue(napi_env env, double value)
    {
        napi_value result;
        radapter::checkNapi("create napi double", env, napi_create_double(
            env,
            value,
            &result
        ));
        return result;
    }

    // Integer specializations.
    template <> napi_value napiValue(napi_env env, int8_t value)
    {
        return radapter::napiValue<int32_t>(env, value);
    }

    template <> napi_value napiValue(napi_env env, int16_t value)
    {
        return radapter::napiValue<int32_t>(env, value);
    }

    template <> napi_value napiValue(napi_env env, int32_t value)
    {
        napi_value result;
        radapter::checkNapi("create napi int32", env, napi_create_int32(
            env,
            value,
            &result
        ));
        return result;
    }

    template <> napi_value napiValue(napi_env env, int64_t value)
    {
        napi_value result;
        radapter::checkNapi("create napi int64", env, napi_create_int64(
            env,
            value,
            &result
        ));
        return result;
    }

    template <> napi_value napiValue(napi_env env, uint8_t value)
    {
        return radapter::napiValue<uint32_t>(env, value);
    }

    template <> napi_value napiValue(napi_env env, uint16_t value)
    {
        return radapter::napiValue<uint32_t>(env, value);
    }

    template <> napi_value napiValue(napi_env env, uint32_t value)
    {
        napi_value result;
        radapter::checkNapi("create napi uint32", env, napi_create_uint32(
            env,
            value,
            &result
        ));
        return result;
    }

    // String specialization.
    template <> napi_value napiValue(napi_env env, const char* value)
    {
        return radapter::napiValue(env, std::string(value));
    }

    template <> napi_value napiValue(napi_env env, std::string value)
    {
        napi_value result;
        radapter::checkNapi("create napi utf8 string", env, napi_create_string_utf8(
            env,
            value.c_str(),
            -1,
            &result
        ));
        return result;
    }
}

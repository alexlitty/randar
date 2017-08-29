#include <limits>
#include <radapter/Utility/NativeValue.hpp>

namespace radapter
{
    // Boolean specialization.
    template <> bool nativeValue(napi_env env, napi_value value)
    {
        napi_value coerced;
        checkNapi("coerce to bool", env, napi_coerce_to_bool(
            env,
            value,
            &coerced
        ));

        bool result;
        checkNapi("get native bool", env, napi_get_value_bool(
            env,
            coerced,
            &result
        ));
        return result;
    }

    // Floating point specializations.
    template <> float nativeValue(napi_env env, napi_value value)
    {
        return static_cast<float>(
            radapter::nativeValue<double>(env, value)
        );
    }

    template <> double nativeValue(napi_env env, napi_value value)
    {
        napi_value coerced;
        checkNapi("coerce to number", env, napi_coerce_to_number(
            env,
            value,
            &coerced
        ));

        double result;
        checkNapi("get native double", env, napi_get_value_double(
            env,
            coerced,
            &result
        ));
        return result;
    }

    // Integer specializations.
    template <> int8_t nativeValue(napi_env env, napi_value value)
    {
        int32_t result = radapter::nativeValue<int32_t>(env, value);
        if (result > std::numeric_limits<int8_t>::max()) {
            throw std::domain_error("Expected 8-bit signed integer");
        }
        return static_cast<int32_t>(result);
    }

    template <> int16_t nativeValue(napi_env env, napi_value value)
    {
        return static_cast<int16_t>(radapter::nativeValue<int32_t>(env, value));
    }

    template <> int32_t nativeValue(napi_env env, napi_value value)
    {
        napi_value coerced;
        checkNapi("coerce to number", env, napi_coerce_to_number(
            env,
            value,
            &coerced
        ));

        int32_t result;
        checkNapi("get native int32", env, napi_get_value_int32(
            env,
            coerced,
            &result
        ));
        return result;
    }

    template <> int64_t nativeValue(napi_env env, napi_value value)
    {
        napi_value coerced;
        checkNapi("coerce to number", env, napi_coerce_to_number(
            env,
            value,
            &coerced
        ));

        int64_t result;
        checkNapi("get native int32", env, napi_get_value_int64(
            env,
            coerced,
            &result
        ));
        return result;
    }

    template <> uint8_t nativeValue(napi_env env, napi_value value)
    {
        uint32_t result = radapter::nativeValue<uint32_t>(env, value);
        if (result > std::numeric_limits<uint8_t>::max() || result < std::numeric_limits<uint8_t>::min()) {
            throw std::runtime_error("Expected 8-bit unsigned integer");
        }
        return static_cast<uint8_t>(result);
    }

    template <> uint16_t nativeValue(napi_env env, napi_value value)
    {
        return static_cast<uint16_t>(radapter::nativeValue<uint32_t>(env, value));
    }

    template <> uint32_t nativeValue(napi_env env, napi_value value)
    {
        napi_value coerced;
        checkNapi("coerce to number", env, napi_coerce_to_number(
            env,
            value,
            &coerced
        ));

        uint32_t result;
        checkNapi("get native uint32", env, napi_get_value_uint32(
            env,
            coerced,
            &result
        ));
        return result;
    }

    // String specializations.
    template <> std::string nativeValue(napi_env env, napi_value value)
    {
        napi_value coerced;
        checkNapi("coerce to string", env, napi_coerce_to_string(
            env,
            value,
            &coerced
        ));

        size_t length;
        checkNapi("get string length", env, napi_get_value_string_utf8(
            env,
            coerced,
            nullptr,
            0,
            &length
        ));

        char *result = new char[length];
        checkNapi("get native string", env, napi_get_value_string_utf8(
            env,
            coerced,
            result,
            length,
            nullptr
        ));
        return std::string(result, length);
    }
}

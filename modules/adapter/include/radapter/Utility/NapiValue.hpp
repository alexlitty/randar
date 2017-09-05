#ifndef RADAPTER_UTILITY_NAPI_VALUE_HPP
#define RADAPTER_UTILITY_NAPI_VALUE_HPP

#include <radapter/Utility/CheckNapi.hpp>

namespace radapter
{
    /**
     * Empty value retrievers.
     *
     * Undefined and null are special values which must be retrieved, not
     * created.
     */
    napi_value napiUndefinedValue(napi_env env);
    napi_value napiNullValue(napi_env env);

    /**
     * Base napiValue template.
     *
     * A specialization must be used.
     */
    template <typename T> struct compileTimeFalse : std::false_type { };
    template <typename T> napi_value napiValue(napi_env env, T value)
    {
        // Asserts false if this base case is ever selected.
        static_assert(compileTimeFalse<T>::value, "Conversion not implemented");

        // Prevent the compiler from complaining about no return value.
        return 0;
    }

    /**
     * Floating point specializations.
     *
     * Floats are converted to doubles.
     */
    template <> napi_value napiValue(napi_env env, float value);
    template <> napi_value napiValue(napi_env env, double value);

    /**
     * Integer specializations.
     *
     * JavaScript does not support typical integer types. They are represented
     * as Numbers, which have enough precision to accurately represent 32 bit
     * integers.
     *
     * A 64 bit integer "type" is exposed through N-API but only as a
     * convenience. It does not offer accurate precision through the entire
     * 64 bit range. For this reason, I suspect, an unsigned equivalent is not
     * exposed.
     */
    template <> napi_value napiValue(napi_env env, int8_t value);
    template <> napi_value napiValue(napi_env env, int16_t value);
    template <> napi_value napiValue(napi_env env, int32_t value);
    template <> napi_value napiValue(napi_env env, int64_t value);

    template <> napi_value napiValue(napi_env env, uint8_t value);
    template <> napi_value napiValue(napi_env env, uint16_t value);
    template <> napi_value napiValue(napi_env env, uint32_t value);

    /**
     * String specialization.
     *
     * Strings are treated as UTF-8 here. While they are not natively treated as
     * such, it suffices for Randar's needs.
     */
    template <> napi_value napiValue(napi_env env, const char* value);
    template <> napi_value napiValue(napi_env env, std::string value);
}

#endif

#ifndef RADAPTER_UTILITY_NATIVE_VALUE_HPP
#define RADAPTER_UTILITY_NATIVE_VALUE_HPP

#include <radapter/Utility/CheckNapi.hpp>

namespace radapter
{
    /**
     * Base nativeValue template.
     *
     * A specialization must be used.
     */
    template <typename T>
    T nativeValue(napi_env env, napi_value value)
    {
        throw std::runtime_error("Not implemented");
    }

    /**
     * Boolean specialization.
     */
    template <> bool nativeValue(napi_env env, napi_value value);

    /**
     * Floating point specializations.
     */
    template <> float nativeValue(napi_env env, napi_value value);
    template <> double nativeValue(napi_env env, napi_value value);

    /**
     * Integer specializations.
     *
     * See napiValue comments.
     */
    template <> int8_t nativeValue(napi_env env, napi_value value);
    template <> int16_t nativeValue(napi_env env, napi_value value);
    template <> int32_t nativeValue(napi_env env, napi_value value);
    template <> int64_t nativeValue(napi_env env, napi_value value);

    template <> uint8_t nativeValue(napi_env env, napi_value value);
    template <> uint16_t nativeValue(napi_env env, napi_value value);
    template <> uint32_t nativeValue(napi_env env, napi_value value);

    /**
     * String specializations.
     *
     * See napiValue comments.
     */
    template <> std::string nativeValue(napi_env env, napi_value value);
}

#endif

#include <radapter/Utility/NativeValue.hpp>

namespace radapter
{
    template <> float nativeValue(napi_env env, napi_value value)
    {
        return static_cast<float>(
            radapter::nativeValue<double>(env, value)
        );
    }

    template <> double nativeValue(napi_env env, napi_value value)
    {
        double result;
        checkNapi("get native double", env, napi_get_value_double(
            env,
            value,
            &result
        ));
        return result;
    }
}

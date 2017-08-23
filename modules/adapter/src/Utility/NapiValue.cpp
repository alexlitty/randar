#include <radapter/Utility/NapiValue.hpp>
#include <iostream>

namespace radapter
{
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

    template <> napi_value napiValue(napi_env env, float value)
    {
        return radapter::napiValue<double>(env, value);
    }
}

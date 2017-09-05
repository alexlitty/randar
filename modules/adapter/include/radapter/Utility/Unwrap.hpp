#ifndef RADAPTER_UTILITY_UNWRAP_HPP
#define RADAPTER_UTILITY_UNWRAP_HPP

#include <radapter/Utility/CallbackInfo.hpp>

namespace radapter
{
    struct unwrap
    {
        /**
        * Callback unwrapper.
        *
        * Accepts an N-API callback, unwraps argument data, and forwards the call
        * to a provided static function T.
        */
        template <radapter::Callback T>
        static napi_value cb(napi_env env, napi_callback_info info)
        {
            CallbackInfo unwrappedInfo(env, info);
            return T(unwrappedInfo);
        }
    };
}

#endif

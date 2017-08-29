#ifndef RADAPTER_UTILITY_UNWRAP_HPP
#define RADAPTER_UTILITY_UNWRAP_HPP

#include <radapter/Utility/CallbackInfo.hpp>

namespace radapter
{
    struct unwrap
    {
        /**
         * Native object unwrapper.
         */
        template <typename T>
        static T& object(napi_env env, napi_value value)
        {
            void *result = nullptr;
            checkNapi("unwrap native object", env, napi_unwrap(
                env,
                value,
                &result
            ));
            return *reinterpret_cast<T*>(result);
        }

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

            try {
                return T(unwrappedInfo);
            }

            catch (const std::runtime_error& err) {
                checkNapi("throw napi error", env, napi_throw_error(
                    env,
                    nullptr,
                    err.what()
                ));
                return 0;
            }
        }
    };
}

#endif

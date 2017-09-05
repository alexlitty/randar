#ifndef RADAPTER_UTILITY_CALLBACK_INFO_HPP
#define RADAPTER_UTILITY_CALLBACK_INFO_HPP

#define RADAPTER_MAX_CALLBACK_ARGC 10

#include <vector>
#include <radapter/Utility/CheckNapi.hpp>

namespace radapter
{
    /**
     * Lightweight structure for extracting callback information.
     *
     * Arguments exceeding index RADAPTER_MAX_CALLBACK_ARGC are discarded.
     */
    struct CallbackInfo
    {
        /**
         * N-API environment hint.
         * 
         * This value cannot be cached around, so neither should this struct.
         */
        napi_env env;

        /**
         * "this" argument in Node.js.
         */
        napi_value self;

        /**
         * Arguments passed to the callback.
         */
        std::vector<napi_value> args;

        /**
         * Constructor.
         */
        CallbackInfo(napi_env env, napi_callback_info info);
    };
}

#endif

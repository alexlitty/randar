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
        napi_value self;
        std::vector<napi_value> args;

        CallbackInfo(napi_env env, napi_callback_info info);
    };
}

#endif

#ifndef RADAPTER_UTILITY_CHECK_NAPI_HPP
#define RADAPTER_UTILITY_CHECK_NAPI_HPP

#include <stdexcept>
#include <node/node_api.h>

namespace radapter
{
    void checkNapi(napi_env, napi_status status);
}

#endif

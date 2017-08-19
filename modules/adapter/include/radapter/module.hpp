#ifndef RANDAR_ADAPTER_MODULE_HPP
#define RANDAR_ADAPTER_MODULE_HPP

#include <node/node_api.h>

namespace radapter
{
    /**
     * Node module initializer.
     */
    void init(napi_env env, napi_value exports, napi_value module, void* priv);
}

/**
 * Register the node module initializer.
 */
NAPI_MODULE(addon, radapter::init);

#endif

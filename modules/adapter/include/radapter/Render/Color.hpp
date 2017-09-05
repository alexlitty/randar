#ifndef RANDAR_ADAPTER_RENDER_COLOR_HPP
#define RANDAR_ADAPTER_RENDER_COLOR_HPP

#include <radapter/Utility/CallbackInfo.hpp>
#include <randar/Render/Color.hpp>

namespace radapter
{
    struct Color
    {
        static std::string className;
        static std::vector<napi_property_descriptor> properties();
        static randar::Color* instance(napi_env, radapter::CallbackInfo& info);
    };
}

#endif

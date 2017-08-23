#ifndef RANDAR_ADAPTER_RENDER_COLOR_HPP
#define RANDAR_ADAPTER_RENDER_COLOR_HPP

#include <radapter/Utility/Unwrap.hpp>
#include <randar/Render/Color.hpp>

namespace radapter
{
    struct Color
    {
        static std::string className;
        static std::vector<napi_property_descriptor> properties();
        static randar::Color* instance(radapter::CallbackInfo& info);

        static napi_value rGet(CallbackInfo& info);
    };
}

#endif

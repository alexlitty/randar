#ifndef RANDAR_ADAPTER_RENDER_COLOR_HPP
#define RANDAR_ADAPTER_RENDER_COLOR_HPP

#include <radapter/Utility/PropertyDescriptor.hpp>
#include <randar/Render/Color.hpp>

namespace radapter
{
    struct Color
    {
        static std::string className;

        /**
         * Meta methods.
         */
        static std::vector<napi_property_descriptor> properties();
        static randar::Color* instance(radapter::CallbackInfo& info);

        /**
         * Channel getters and setters via floats.
         */
        static napi_value r(CallbackInfo& info);
        static napi_value g(CallbackInfo& info);
        static napi_value b(CallbackInfo& info);
        static napi_value a(CallbackInfo& info);

        /**
         * Channel getters and setters via integers.
         */
        static napi_value rInt(CallbackInfo& info);
        static napi_value gInt(CallbackInfo& info);
        static napi_value bInt(CallbackInfo& info);
        static napi_value aInt(CallbackInfo& info);
    };
}

#endif

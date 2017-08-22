#include <radapter/Render/Color.hpp>

std::string radapter::Color::className = "Color";

std::vector<napi_property_descriptor> radapter::Color::properties()
{
    return std::vector<napi_property_descriptor>();
}

randar::Color* radapter::Color::instance(napi_env env, radapter::CallbackInfo& info)
{
    return new randar::Color();
}

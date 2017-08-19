#include <radapter/Render/Color.hpp>

std::string radapter::Color::name = "Color";

std::vector<napi_property_descriptor> radapter::Color::properties()
{
    return std::vector<napi_property_descriptor>();
}

randar::Color* radapter::Color::instance(napi_env env, radapter::CallbackInfo& info)
{
    return new randar::Color();
}

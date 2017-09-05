#include <radapter/Render/Color.hpp>

std::string radapter::Color::className = "Color";

std::vector<napi_property_descriptor> radapter::Color::properties()
{
    return {
        radapter::getter<radapter::Color::rGet>("r"),
        radapter::setter<radapter::Color::rSet>("r")
    };
}

randar::Color* radapter::Color::instance(radapter::CallbackInfo& info)
{
    return new randar::Color();
}

napi_value radapter::Color::rGet(radapter::CallbackInfo& info)
{
    return napiValue(info.env, info.unwrap<randar::Color>().r());
}

napi_value radapter::Color::rSet(radapter::CallbackInfo& info)
{
    info.unwrap<randar::Color>().r(
        radapter::nativeValue<float>(info.env, info.args[0])
    );

    return info.args[0];
}

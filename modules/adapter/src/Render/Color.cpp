#include <radapter/Render/Color.hpp>

std::string radapter::Color::className = "Color";

std::vector<napi_property_descriptor> radapter::Color::properties()
{
    std::vector<napi_property_descriptor> props;

    napi_property_descriptor d = {
        "r",
        0,

        0,
        radapter::Color::rGet,
        0,
        0,

        napi_default,
        0
    };

    props.push_back(d);

    return props;
}

randar::Color* radapter::Color::instance(radapter::CallbackInfo& info)
{
    return new randar::Color();
}

napi_value radapter::Color::rGet(napi_env env, napi_callback_info ci)
{
    CallbackInfo info(env, ci);
    auto color = info.unwrap<randar::Color>();
    return napiValue(env, color.r());
}

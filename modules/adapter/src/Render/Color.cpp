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

    return std::vector<napi_property_descriptor>();
}

randar::Color* radapter::Color::instance(radapter::CallbackInfo& info)
{
    return new randar::Color();
}

napi_value radapter::Color::rGet(napi_env env, napi_callback_info)
{
    napi_value result;
    checkNapi("creating double", env, napi_create_double(env, 0.0f, &result));
    return result;
}

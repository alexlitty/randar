#include <radapter/Render/Color.hpp>

std::string radapter::Color::className = "Color";

std::vector<napi_property_descriptor> radapter::Color::properties()
{
    std::vector<napi_property_descriptor> props;

    napi_property_descriptor d = {
        "r",
        0,

        0,
        radapter::unwrap::cb<radapter::Color::rGet>,
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

napi_value radapter::Color::rGet(radapter::CallbackInfo& info)
{
    return napiValue(info.env, info.unwrap<randar::Color>().r());
}

#include <radapter/Render/Color.hpp>

std::string radapter::Color::className = "Color";

// Meta methods.
std::vector<napi_property_descriptor> radapter::Color::properties()
{
    return {
        radapter::methodProperty<radapter::Color::r>("r"),
        radapter::methodProperty<radapter::Color::g>("g"),
        radapter::methodProperty<radapter::Color::b>("b"),
        radapter::methodProperty<radapter::Color::a>("a"),

        radapter::methodProperty<radapter::Color::rInt>("rInt")
    };
}

randar::Color* radapter::Color::instance(radapter::CallbackInfo& info)
{
    return new randar::Color();
}

// Channel getters and setters.
napi_value radapter::Color::r(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.r(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.r());
}

napi_value radapter::Color::g(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.g(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.g());
}

napi_value radapter::Color::b(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.b(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.b());
}

napi_value radapter::Color::a(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.a(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.a());
}

// Channel getters and setters via integers.
napi_value radapter::Color::rInt(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.rInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.rInt());
}

napi_value radapter::Color::gInt(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.gInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.gInt());
}

napi_value radapter::Color::bInt(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.bInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.bInt());
}

napi_value radapter::Color::aInt(radapter::CallbackInfo& info)
{
    auto &color = info.unwrap<randar::Color>();

    if (info.args.size()) {
        color.aInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.aInt());
}

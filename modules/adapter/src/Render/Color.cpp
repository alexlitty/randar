#include <radapter/Render/Color.hpp>
#include <radapter/Utility/Classinator.hpp>

std::string radapter::Color::className = "Color";

// Meta methods.
std::vector<napi_property_descriptor> radapter::Color::properties()
{
    return {
        radapter::methodProperty<radapter::Color::set>("set"),
        radapter::methodProperty<radapter::Color::r>("r"),
        radapter::methodProperty<radapter::Color::g>("g"),
        radapter::methodProperty<radapter::Color::b>("b"),
        radapter::methodProperty<radapter::Color::a>("a"),

        radapter::methodProperty<radapter::Color::setInt>("setInt"),
        radapter::methodProperty<radapter::Color::rInt>("rInt"),
        radapter::methodProperty<radapter::Color::gInt>("gInt"),
        radapter::methodProperty<radapter::Color::bInt>("bInt"),
        radapter::methodProperty<radapter::Color::aInt>("aInt"),

        radapter::methodProperty<radapter::Color::vary>("vary"),
        radapter::methodProperty<radapter::Color::varied>("varied")
    };
}

randar::Color* radapter::Color::instance(radapter::CallbackInfo& info)
{
    float r = 0, g = 0, b = 0, a = 1;
    if (info.args.size() > 0) {
        r = nativeValue<float>(info.env, info.args[0]);
    }
    if (info.args.size() > 1) {
        g = nativeValue<float>(info.env, info.args[1]);
    }
    if (info.args.size() > 2) {
        b = nativeValue<float>(info.env, info.args[2]);
    }
    if (info.args.size() > 3) {
        a = nativeValue<float>(info.env, info.args[3]);
    }
    return new randar::Color(r, g, b, a);
}

// Channel getters and setters.
napi_value radapter::Color::set(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size() < 3) {
        throw std::runtime_error("Invalid number of arguments");
    }

    float r = nativeValue<float>(info.env, info.args[0]);
    float g = nativeValue<float>(info.env, info.args[1]);
    float b = nativeValue<float>(info.env, info.args[2]);

    float a;
    if (info.args.size() > 3) {
        a = nativeValue<float>(info.env, info.args[3]);
    } else {
        a = 1.0f;
    }

    color.set(r, g, b, a);
    return info.self;
}

napi_value radapter::Color::r(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.r(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.r());
}

napi_value radapter::Color::g(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.g(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.g());
}

napi_value radapter::Color::b(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.b(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.b());
}

napi_value radapter::Color::a(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.a(radapter::nativeValue<float>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.a());
}

// Channel getters and setters via integers.
napi_value radapter::Color::setInt(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size() < 3) {
        throw std::runtime_error("Invalid number of arguments");
    }

    uint8_t r = nativeValue<uint8_t>(info.env, info.args[0]);
    uint8_t g = nativeValue<uint8_t>(info.env, info.args[1]);
    uint8_t b = nativeValue<uint8_t>(info.env, info.args[2]);

    uint8_t a;
    if (info.args.size() > 3) {
        a = nativeValue<uint8_t>(info.env, info.args[3]);
    } else {
        a = 255;
    }

    color.setInt(r, g, b, a);
    return info.self;
}

napi_value radapter::Color::rInt(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.rInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.rInt());
}

napi_value radapter::Color::gInt(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.gInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.gInt());
}

napi_value radapter::Color::bInt(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.bInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.bInt());
}

napi_value radapter::Color::aInt(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    if (info.args.size()) {
        color.aInt(radapter::nativeValue<uint8_t>(info.env, info.args[0]));
        return info.self;
    }

    return napiValue(info.env, color.aInt());
}

// Variance methods.
napi_value radapter::Color::vary(radapter::CallbackInfo& info)
{
    if (info.args.size()) {
        auto &color = unwrap::object<randar::Color>(info.env, info.self);
        auto &other = unwrap::object<randar::Color>(info.env, info.args[0]);

        bool varyAlpha;
        if (info.args.size() > 1) {
            varyAlpha = nativeValue<bool>(info.env, info.args[1]);
        } else {
            varyAlpha = false;
        }

        color.vary(other, varyAlpha);
    }

    return info.self;
}

napi_value radapter::Color::varied(radapter::CallbackInfo& info)
{
    auto &color = unwrap::object<randar::Color>(info.env, info.self);

    napi_value constructor = Classinator<radapter::Color, randar::Color>::constructor(info.env);
    napi_value value;
    checkNapi("create new js instance", info.env, napi_new_instance(
        info.env,
        constructor,
        0,
        nullptr,
        &value
    ));

    auto &result = unwrap::object<randar::Color>(info.env, value);
    result = color;

    if (info.args.size()) {
        auto &other = unwrap::object<randar::Color>(info.env, info.args[0]);

        bool varyAlpha;
        if (info.args.size() > 1) {
            varyAlpha = nativeValue<bool>(info.env, info.args[1]);
        } else {
            varyAlpha = false;
        }

        result.varied(other, varyAlpha);
    }

    return value;
}

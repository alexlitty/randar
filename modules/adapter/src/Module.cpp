#include <radapter/Module.hpp>
#include <radapter/Render/Color.hpp>
#include <radapter/Utility/Classinator.hpp>

void radapter::init(napi_env env, napi_value exports, napi_value module, void* priv)
{
    std::string name = "Color";
    napi_value nodeString;
    napi_create_string_utf8(
        env,
        name.c_str(),
        name.length(),
        &nodeString
    );

    napi_set_property(
        env,
        exports,
        nodeString,
        radapter::Classinator<radapter::Color, randar::Color>::constructor(env)
    );
}

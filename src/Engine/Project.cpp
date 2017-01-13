#include <randar/Engine/Project.hpp>

std::string randar::Project::toJson() const
{
    Awesomium::JSObject result;

    result.SetProperty(Awesomium::WSLit("textures"), randar::toJs(this->textures));

    return randar::toJson(result);
}

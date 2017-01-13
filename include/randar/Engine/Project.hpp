#ifndef RANDAR_ENGINE_PROJECT_HPP
#define RANDAR_ENGINE_PROJECT_HPP

#include <randar/Render/Texture.hpp>
#include <randar/Utility/Awesomium.hpp>
#include <randar/Utility/Map.hpp>

namespace randar
{
    template <typename T>
    Awesomium::JSObject toJs(const std::map<std::string, T*>& objects)
    {
        Awesomium::JSObject result;

        for (auto item : objects) {
            result.SetProperty(Awesomium::ToWebString(item.first), item.second->toJs());
        }

        return result;
    }

    struct Project
    {
        std::string name;
        std::map<std::string, Texture*> textures;

        /**
         * Generates a JSON representation of the project.
         */
        std::string toJson() const;
    };
}

#endif

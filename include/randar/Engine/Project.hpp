#ifndef RANDAR_ENGINE_PROJECT_HPP
#define RANDAR_ENGINE_PROJECT_HPP

#include <randar/Render/Texture.hpp>
#include <randar/Utility/Map.hpp>

namespace randar
{
    struct Project
    {
        std::string name;
        std::map<std::string, Texture> textures;
    };
}

#endif

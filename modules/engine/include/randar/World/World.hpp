#ifndef RANDAR_WORLD_WORLD_HPP
#define RANDAR_WORLD_WORLD_HPP

#include <randar/Render/Light/LightCollection.hpp>
#include <randar/Render/ModelCollection.hpp>

namespace randar
{
    struct World
    {
        Color backgroundColor;
        ModelCollection models;
        LightCollection lights;
    };

    World world();
}

#endif

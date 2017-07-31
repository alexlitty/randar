#ifndef RANDAR_WORLD_WORLD_HPP
#define RANDAR_WORLD_WORLD_HPP

#include <randar/Render/ModelCollection.hpp>

namespace randar
{
    struct World
    {
        Color backgroundColor;
        ModelCollection models;
    };

    World world();
}

#endif

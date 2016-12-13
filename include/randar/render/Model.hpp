#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/math/Transformable.hpp>
#include <randar/render/Material.hpp>
#include <randar/render/Vertices.hpp>

namespace randar
{
    struct Model : public Transformable
    {
        Vertices vertices;
    };
}

#endif

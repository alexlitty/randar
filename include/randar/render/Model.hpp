#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/render/Drawable.hpp>
#include <randar/render/Material.hpp>
#include <randar/render/Vertices.hpp>

namespace randar
{
    struct Model : virtual public Drawable
    {
        Vertices vertices;

        void draw() const;
    };
}

#endif

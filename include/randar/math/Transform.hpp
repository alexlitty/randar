#ifndef RANDAR_RENDER_TRANSFORM_HPP
#define RANDAR_RENDER_TRANSFORM_HPP

#include <randar/math/Transformable.hpp>

namespace randar
{
    struct Transform : public Transformable
    {
        glm::mat4 getMatrix() const;
    };
}

#endif

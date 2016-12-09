#ifndef RANDAR_RENDER_TRANSFORM_HPP
#define RANDAR_RENDER_TRANSFORM_HPP

#include <glm/mat4x4.hpp>
#include <randar/math/Vector.hpp>

namespace randar
{
    class Transform
    {
        Vector position;
        float scale;

        glm::mat4 matrix;
        void updateMatrix();

    public:
        Transform();

        void setPosition(Vector newPosition);
        void move(Vector relativePosition);
        Vector getPosition() const;

        glm::mat4 getMatrix() const;
    };
}

#endif

#ifndef RANDAR_RENDER_CAMERA_HPP
#define RANDAR_RENDER_CAMERA_HPP

#include <randar/math/Vector.hpp>
#include <randar/utility.hpp>

namespace randar
{
    class Camera
    {
        Vector position;
        Vector target;

        glm::mat4 view;
        glm::mat4 projection;

        /**
         * Updates the view and projection matrices.
         */
        void updateMatrices();

    public:
        Camera();

        void setPosition(Vector newPosition);
        Vector getPosition() const;

        void setTarget(Vector newTarget);
        Vector getTarget() const;

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
    };
}

#endif

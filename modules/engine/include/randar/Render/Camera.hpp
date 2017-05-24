#ifndef RANDAR_RENDER_CAMERA_HPP
#define RANDAR_RENDER_CAMERA_HPP

#include <randar/Math.hpp>
#include <randar/Render/Viewport.hpp>

namespace randar
{
    class Camera : virtual public Transform
    {
        bool isOrtho = false;
        float orthoLeft = 0;
        float orthoRight = 1;
        float orthoBottom = 0;
        float orthoTop = 1;

        Angle fov = 45.0f;
        float aspectRatio = 4.0f / 3.0f;
        float nearZ = 0.1f;
        float farZ = 100.0f;

        Vector3 targ;

        mutable glm::mat4 view;
        mutable glm::mat4 proj;

        /**
         * Updates the view and projection matrices.
         */
        void updateMatrices() const;

    public:
        Viewport viewport;
        Camera();

        void ortho();
        void ortho(float left, float right, float bottom, float top);
        void projection();

        /**
         * Sets and retrieves the position that the camera is pointed at.
         */
        void target(Vector3 newTarget);
        Vector3 target() const;

        void fieldOfView(float newFieldOfView);

        /**
         * Moves the camera perpendicularly.
         */
        void pan(float x, float y);

        glm::mat4 viewMatrix() const;
        glm::mat4 projectionMatrix() const;
    };
}

#endif

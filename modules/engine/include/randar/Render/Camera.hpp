#ifndef RANDAR_RENDER_CAMERA_HPP
#define RANDAR_RENDER_CAMERA_HPP

#include <randar/Math/Transform.hpp>
#include <randar/Render/Viewport.hpp>

namespace randar
{
    enum class CameraType
    {
        NONE,
        ORTHO,
        PROJECTION
    };

    class Camera : public Transform
    {
        CameraType type = CameraType::NONE;

        float orthoLeft = 0;
        float orthoRight = 1;
        float orthoBottom = 0;
        float orthoTop = 1;

        Angle fov = 45.0f;
        float aspectRatio = 4.0f / 3.0f;
        float nearZ = 0.1f;
        float farZ = 1000.0f;

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

        /**
         * Sets the near and far Z.
         */
        void range(float newNearZ, float newFarZ);

        glm::mat4 viewMatrix() const;
        glm::mat4 projectionMatrix() const;
    };
}

#endif

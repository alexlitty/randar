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

        Angle fieldOfView = 45.0f;
        float aspectRatio = 4.0f / 3.0f;
        float nearZ = 0.1f;
        float farZ = 100.0f;

        Vector3 target;

        glm::mat4 view;
        glm::mat4 projection;

        /**
         * Updates the view and projection matrices.
         */
        virtual void onTransform() override;
        void updateMatrices();

    public:
        Viewport viewport;
        Camera();

        void setOrtho();
        void setOrtho(float left, float right, float bottom, float top);
        void disableOrtho();

        /**
         * Sets and retrieves the position that the camera is pointed at.
         */
        void setTarget(Vector3 newTarget);
        Vector3 getTarget() const;

        void setFieldOfView(float newFieldOfView);

        /**
         * Moves the camera perpendicularly.
         */
        void pan(float x, float y);

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
    };
}

#endif

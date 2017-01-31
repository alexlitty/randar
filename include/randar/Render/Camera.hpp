#ifndef RANDAR_RENDER_CAMERA_HPP
#define RANDAR_RENDER_CAMERA_HPP

#include <randar/Math.hpp>
#include <randar/Render/Viewport.hpp>

namespace randar
{
    class Camera : virtual public Transformable
    {
        bool isOrtho;
        float orthoLeft;
        float orthoRight;
        float orthoTop;
        float orthoBottom;

        Angle fieldOfView;
        float aspectRatio;
        float nearZ;
        float farZ;

        Vector target;

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

        void setOrtho(float left, float right, float top, float bottom);
        void disableOrtho();

        /**
         * Sets and retrieves the position that the camera is pointed at.
         */
        void setTarget(Vector newTarget);
        Vector getTarget() const;

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

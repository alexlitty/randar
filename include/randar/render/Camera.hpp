#ifndef RANDAR_RENDER_CAMERA_HPP
#define RANDAR_RENDER_CAMERA_HPP

#include <randar/Math.hpp>
#include <randar/render/Viewport.hpp>

namespace randar
{
    class Camera : virtual public Transformable
    {
        bool isOrtho;
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

        void setOrtho(bool ortho);

        void setTarget(Vector newTarget);
        Vector getTarget() const;

        void setFieldOfView(float newFieldOfView);

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
    };
}

#endif

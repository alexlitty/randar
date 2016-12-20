#ifndef RANDAR_PHYSICS_PHYSICAL_HPP
#define RANDAR_PHYSICS_PHYSICAL_HPP

#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/render/Drawable.hpp>

namespace randar
{
    class Physical : virtual public Drawable
    {
    protected:
        btRigidBody *body;

        /**
         * Sync the rendering transform to the physical transform.
         */
        void writeMotionState();

        /**
         * Sync the physical transform to the rendering transform.
         */
        void readMotionState();

    public:
        Physical();
        virtual ~Physical();

        void createBody(const btRigidBody::btRigidBodyConstructionInfo& info);
        void destroyBody();
        btRigidBody* getBody();

        virtual void onTransform() override;
    };
}

#endif

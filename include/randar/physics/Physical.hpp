#ifndef RANDAR_PHYSICS_PHYSICAL_HPP
#define RANDAR_PHYSICS_PHYSICAL_HPP

#include <stdexcept>
#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/render/Drawable.hpp>

namespace randar
{
    class Physical : virtual public Drawable
    {
    protected:
        btRigidBody *body;
        btMotionState *motionState;
        btCollisionShape *collisionShape;

    public:
        Physical();
        virtual ~Physical();

        void createBody(float mass);
        void destroyBody();
        btRigidBody* getBody();

        /**
         * Sync the physical and rendering transforms.
         */
        void readMotionState();
        void writeMotionState();
        virtual void onTransform() override;
    };
}

#endif

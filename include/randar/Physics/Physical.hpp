#ifndef RANDAR_PHYSICS_PHYSICAL_HPP
#define RANDAR_PHYSICS_PHYSICAL_HPP

#include <stdexcept>
#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/Math/Transformable.hpp>
#include <randar/Shape.hpp>

namespace randar
{
    class Physical : virtual public Transformable
    {
    protected:
        btRigidBody *body;
        btMotionState *motionState;
        btCollisionShape *collisionShape;
        Mesh collisionMesh;

    public:
        Physical();
        virtual ~Physical();

        void createBody(float mass, btCollisionShape *newCollisionShape);
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

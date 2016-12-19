#ifndef RANDAR_PHYSICS_SYSTEM_HPP
#define RANDAR_PHYSICS_SYSTEM_HPP

#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/Math.hpp>

namespace randar
{
    class System
    {
        btDefaultCollisionConfiguration collisionConfiguration;
        btCollisionDispatcher dispatcher;
        btBroadphaseInterface *overlappingPairCache;
        btSequentialImpulseConstraintSolver solver;
        btDiscreteDynamicsWorld world;

    public:
        System();
        ~System();
    };
}

#endif

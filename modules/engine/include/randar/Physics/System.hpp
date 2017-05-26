#ifndef RANDAR_PHYSICS_SYSTEM_HPP
#define RANDAR_PHYSICS_SYSTEM_HPP

#include <vector>
#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/Math/Vector3.hpp>
#include <randar/Physics/Physical.hpp>

namespace randar
{
    class System
    {
        btDefaultCollisionConfiguration collisionConfiguration;
        btCollisionDispatcher dispatcher;
        btBroadphaseInterface *overlappingPairCache;
        btSequentialImpulseConstraintSolver solver;
        btDiscreteDynamicsWorld world;

        std::vector<Physical*> objects;

    public:
        System();
        ~System();

        void add(Physical* object);

        void step();
    };
}

#endif

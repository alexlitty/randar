#include <randar/physics/System.hpp>

randar::System::System()
: dispatcher(&collisionConfiguration),
  overlappingPairCache(new btDbvtBroadphase()),
  world(&dispatcher, overlappingPairCache, &solver, &collisionConfiguration)
{
    this->world.setGravity(Vector(0, -10, 0));
}

randar::System::~System()
{

}

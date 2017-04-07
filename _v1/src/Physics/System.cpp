#include <randar/Physics/System.hpp>

randar::System::System()
: dispatcher(&collisionConfiguration),
  overlappingPairCache(new btDbvtBroadphase()),
  world(&dispatcher, overlappingPairCache, &solver, &collisionConfiguration)
{
    this->world.setGravity(Vector(0, -0.5f, 0));
}

randar::System::~System()
{

}

void randar::System::add(randar::Physical* object)
{
    if (!object->getBody()) {
        std::runtime_error("Cannot add bodyless object to system");
    }

    this->objects.push_back(object);
    this->world.addRigidBody(object->getBody());
}

void randar::System::step()
{
    this->world.stepSimulation(1, 2, 1.0f / 24.0f);

    for (auto object : this->objects) {
        object->readMotionState();
    }
}

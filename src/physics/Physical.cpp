#include <randar/physics/Physical.hpp>

randar::Physical::Physical()
: body(nullptr),
  motionState(new btDefaultMotionState()),
  collisionShape(nullptr)
{

}

randar::Physical::~Physical()
{
    this->destroyBody();
    delete this->motionState;
    delete this->collisionShape;
}

void randar::Physical::createBody(float mass)
{
    if (!this->collisionShape) {
        std::runtime_error("Cannot create physical body without collision shape");
    }

    this->destroyBody();
    this->body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
        mass,
        this->motionState,
        this->collisionShape
    ));
}

void randar::Physical::destroyBody()
{
    delete this->body;
    this->body = nullptr;
}

btRigidBody* randar::Physical::getBody()
{
    return this->body;
}

// Sync the rendering and physical transforms.
void randar::Physical::readMotionState()
{
    if (!this->body) {
        return;
    }

    btTransform transform;
    this->motionState->getWorldTransform(transform);
    this->set(transform);
}

void randar::Physical::writeMotionState()
{
    if (!this->body) {
        return;
    }

    this->motionState->setWorldTransform(*this);
}

void randar::Physical::onTransform()
{
    this->writeMotionState();
}

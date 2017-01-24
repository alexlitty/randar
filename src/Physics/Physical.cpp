#include <randar/Physics/Physical.hpp>

randar::Physical::Physical()
: body(nullptr),
  motionState(nullptr),
  collisionShape(nullptr)
{

}

randar::Physical::~Physical()
{
    this->destroyBody();
}

void randar::Physical::createBody(float mass, btCollisionShape *newCollisionShape)
{
    this->destroyBody();

    this->collisionShape = newCollisionShape;
    if (!this->collisionShape) {
        std::runtime_error("Cannot create physical body without collision shape");
    }

    this->motionState = new btDefaultMotionState();
    this->body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
        mass,
        this->motionState,
        this->collisionShape
    ));

    std::string name = this->collisionShape->getName();
    if (name == "STATICPLANE") {
        btVector3 min, max;
        this->collisionShape->getAabb(btTransform::getIdentity(), min, max);
        //this->collisionMesh = Plane(min, max);
    }
}

void randar::Physical::destroyBody()
{
    delete this->body;
    delete this->motionState;
    delete this->collisionShape;

    this->body = nullptr;
    this->motionState = nullptr;
    this->collisionShape = nullptr;
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

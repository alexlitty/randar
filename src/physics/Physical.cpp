#include <randar/physics/Physical.hpp>

randar::Physical::Physical()
: body(nullptr)
{

}

randar::Physical::~Physical()
{
    this->destroyBody();
}

// Sync the rendering transform to the physical transform.
void randar::Physical::writeMotionState()
{
    if (!this->body) {
        return;
    }

    btTransform transform;
    transform.setOrigin(this->getPosition());
    transform.setRotation(this->getRotation());
    this->body->getMotionState()->setWorldTransform(transform);
}

// Sync the physical transform to the rendering transform.
void randar::Physical::readMotionState()
{
    if (!this->body) {
        return;
    }

    btTransform transform;
    this->body->getMotionState()->getWorldTransform(transform);
    this->setPosition(transform.getOrigin());
    this->setRotation(transform.getRotation());
}

void randar::Physical::createBody(const btRigidBody::btRigidBodyConstructionInfo& info)
{
    this->destroyBody();
    this->body = new btRigidBody(info);
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

void randar::Physical::onTransform()
{
    this->writeMotionState();
}

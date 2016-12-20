#include <randar/math/Transformable.hpp>

randar::Transformable::~Transformable()
{

}

// Absolutely sets the position.
void randar::Transformable::setPosition(const randar::Vector& newPosition)
{
    this->position = newPosition;
    this->onTransform();
}

// Relatively sets the position.
void randar::Transformable::move(const randar::Vector& movement)
{
    this->setPosition(
        this->getPosition() + movement
    );
}

void randar::Transformable::move(const randar::Quaternion& angularMovement)
{
    this->setPosition(
        angularMovement.transform(this->getPosition())
    );
}

// Retrieves the position.
randar::Vector randar::Transformable::getPosition() const
{
    return this->position;
}

// Sets the rotation.
void randar::Transformable::setRotation(const randar::Quaternion& quaternion)
{
    this->rotation = quaternion;
    this->onTransform();
}

void randar::Transformable::setRotation(const randar::Vector& axis, const randar::Angle& angle)
{
    this->rotation.set(axis, angle);
    this->onTransform();
}

// Retrieves the rotation.
randar::Quaternion randar::Transformable::getRotation() const
{
    return this->rotation;
}

// Sets and retrieves the axis of rotation.
void randar::Transformable::setRotationAxis(const randar::Vector& axis)
{
    this->rotation.setAxis(axis);
    this->onTransform();
}

randar::Vector randar::Transformable::getRotationAxis() const
{
    return this->rotation.getAxis();
}

// Absolutely sets the angle of rotation.
void randar::Transformable::setAngle(const randar::Angle& angle)
{
    this->rotation.setAngle(angle);
    this->onTransform();
}

// Relatively sets the angle of rotation.
void randar::Transformable::rotate(const randar::Angle& angle)
{
    this->rotation.setAngle(this->rotation.getAngle() + angle);
    this->onTransform();
}

// Retrieves the angle of rotation.
randar::Angle randar::Transformable::getAngle() const
{
    return this->rotation.getAngle();
}

// Function called when a transformation occurs.
void randar::Transformable::onTransform()
{

}

// Retrieves the current transformation matrix.
glm::mat4 randar::Transformable::getTransformMatrix() const
{
    glm::vec3 glmPosition(this->position.x, this->position.y, this->position.z);
    return glm::translate(this->rotation.getMatrix(), glmPosition);
}

// Converts to physics transformation.
randar::Transformable::operator btTransform() const
{
    return btTransform(this->getRotation(), this->getPosition());
}

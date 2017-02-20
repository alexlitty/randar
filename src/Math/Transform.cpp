#include <randar/Math/Transform.hpp>

randar::Transform::~Transform()
{

}

// Sets this transformation from a physical transformation.
void randar::Transform::set(const btTransform& transform)
{
    this->setPosition(transform.getOrigin());
    this->setRotation(transform.getRotation());
}

// Absolutely sets the position.
void randar::Transform::setPosition(const randar::Vector& newPosition)
{
    this->position = newPosition;
    this->onTransform();
}

// Relatively sets the position.
void randar::Transform::move(const randar::Vector& movement)
{
    this->setPosition(
        this->getPosition() + movement
    );
}

void randar::Transform::move(const randar::Quaternion& angularMovement)
{
    this->setPosition(
        angularMovement.transform(this->getPosition())
    );
}

// Retrieves the position.
randar::Vector randar::Transform::getPosition() const
{
    return this->position;
}

// Sets the rotation.
void randar::Transform::setRotation(const randar::Quaternion& quaternion)
{
    this->rotation = quaternion;
    this->onTransform();
}

void randar::Transform::setRotation(const randar::Vector& axis, const randar::Angle& angle)
{
    this->rotation.set(axis, angle);
    this->onTransform();
}

// Retrieves the rotation.
randar::Quaternion randar::Transform::getRotation() const
{
    return this->rotation;
}

// Sets and retrieves the axis of rotation.
void randar::Transform::setRotationAxis(const randar::Vector& axis)
{
    this->rotation.setAxis(axis);
    this->onTransform();
}

randar::Vector randar::Transform::getRotationAxis() const
{
    return this->rotation.getAxis();
}

// Absolutely sets the angle of rotation.
void randar::Transform::setAngle(const randar::Angle& angle)
{
    this->rotation.setAngle(angle);
    this->onTransform();
}

// Relatively sets the angle of rotation.
void randar::Transform::rotate(const randar::Angle& angle)
{
    this->rotation.setAngle(this->rotation.getAngle() + angle);
    this->onTransform();
}

// Retrieves the angle of rotation.
randar::Angle randar::Transform::getAngle() const
{
    return this->rotation.getAngle();
}

// Applies another transform to this transform.
void randar::Transform::apply(const randar::Transform& other)
{
    this->move(other.getPosition());
    // @@@ - Also rotate
}

// Function called when a transformation occurs.
void randar::Transform::onTransform()
{

}

// Retrieves the current transformation matrix.
glm::mat4 randar::Transform::getTransformMatrix() const
{
    glm::vec3 glmPosition(this->position.x, this->position.y, this->position.z);
    return glm::translate(this->rotation.getMatrix(), glmPosition);
}

// Converts to physics transformation.
randar::Transform::operator btTransform() const
{
    return btTransform(this->getRotation(), this->getPosition());
}

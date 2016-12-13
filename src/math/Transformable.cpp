#include <randar/math/Transformable.hpp>

randar::Transformable::~Transformable()
{

}

// Sets the position absolutely.
void randar::Transformable::setPosition(randar::Vector newPosition)
{
    this->position = newPosition;
    this->onTransform();
}

// Sets the position relatively.
void randar::Transformable::move(randar::Vector movement)
{
    this->position += movement;
    this->onTransform();
}

// Sets the position relatively, as an angular movement.
void randar::Transformable::move(randar::Rotation angularMovement)
{
    this->setPosition(
        angularMovement.getQuaternion().transform(this->position)
    );
}

// Retrieves the position.
randar::Vector randar::Transformable::getPosition() const
{
    return this->position;
}

// Sets the rotation.
void randar::Transformable::setRotation(randar::Rotation newRotation)
{
    this->rotation = newRotation;
    this->onTransform();
}

void randar::Transformable::setRotation(const randar::Quaternion& quaternion)
{
    this->rotation.setQuaternion(quaternion);
    this->onTransform();
}

// Sets the rotation, given an axis and angle.
void randar::Transformable::setRotation(randar::Vector axis, randar::Angle angle)
{
    this->rotation = randar::Rotation(axis, angle);
    this->onTransform();
}

// Retrieves the rotation.
randar::Rotation randar::Transformable::getRotation() const
{
    return this->rotation;
}

// Sets the axis of rotation.
void randar::Transformable::setRotationAxis(randar::Vector axis)
{
    this->rotation.setAxis(axis);
    this->onTransform();
}

// Retrieves the axis of rotation.
randar::Vector randar::Transformable::getRotationAxis() const
{
    return this->rotation.getAxis();
}

// Sets the rotation angle absolutely.
void randar::Transformable::setAngle(randar::Angle angle)
{
    this->rotation.setAngle(angle);
    this->onTransform();
}

// Sets the rotation angle relatively.
void randar::Transformable::rotate(randar::Angle angle)
{
    this->rotation.setAngle(this->rotation.getAngle() + angle);
    this->onTransform();
}

// Retrieves the rotation angle.
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

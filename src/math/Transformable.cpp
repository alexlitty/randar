#include <randar/math/Transformable.hpp>

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

// Sets the rotation, given an origin and angle.
void randar::Transformable::setRotation(randar::Vector origin, randar::Angle angle)
{
    this->rotation = randar::Rotation(origin, angle);
    this->onTransform();
}

// Retrieves the rotation.
randar::Rotation randar::Transformable::getRotation() const
{
    return this->rotation;
}

// Sets the origin of rotation.
void randar::Transformable::setRotationOrigin(randar::Vector origin)
{
    this->rotation.setOrigin(origin);
    this->onTransform();
}

// Retrieves the origin of rotation.
randar::Vector randar::Transformable::getRotationOrigin() const
{
    return this->rotation.getOrigin();
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

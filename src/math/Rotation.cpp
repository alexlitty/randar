#include <cmath>
#include <randar/math/Rotation.hpp>

// Default constructor.
randar::Rotation::Rotation()
{

}

// Constructor, given a quaternion.
randar::Rotation::Rotation(const randar::Quaternion& newQuaternion)
{
    this->quaternion = newQuaternion;
}

// Constructor, given an origin and angle.
randar::Rotation::Rotation(randar::Vector newOrigin, randar::Angle newAngle)
{
    this->set(newOrigin, newAngle);
}

// Sets the quaternion based on the origin and angle.
void randar::Rotation::updateQuaternion()
{
    float halfRads = this->angle.toRadians() / 2;
    Vector transformedOrigin = this->origin * std::sin(halfRads);

    this->quaternion.w = std::cos(halfRads);
    this->quaternion.x = transformedOrigin.x;
    this->quaternion.y = transformedOrigin.y;
    this->quaternion.z = transformedOrigin.z;
}

// Updates the origin and angle described by the quaternion.
void randar::Rotation::readQuaternion()
{
    float halfRads = std::acos(this->quaternion.w);
    this->angle = halfRads * 2.0f;

    float sin = std::sin(halfRads);
    this->origin.x = this->quaternion.x / sin;
    this->origin.y = this->quaternion.y / sin;
    this->origin.z = this->quaternion.z / sin;
}

// Sets the origin and angle.
void randar::Rotation::set(randar::Vector newOrigin, randar::Angle newAngle)
{
    this->origin = newOrigin;
    this->angle = newAngle;
    this->updateQuaternion();
}

// Sets and retrieves origin.
void randar::Rotation::setOrigin(randar::Vector newOrigin)
{
    this->set(newOrigin, this->angle);
}

randar::Vector randar::Rotation::getOrigin() const
{
    return this->origin;
}

// Sets and retrieves angle.
void randar::Rotation::setAngle(randar::Angle newAngle)
{
    this->set(this->origin, newAngle);
}

randar::Angle randar::Rotation::getAngle() const
{
    return this->angle;
}

// Transforms a vector.
randar::Vector randar::Rotation::transform(randar::Vector vector) const
{
    return vector *= this->getMatrix();
}

// Retrieves quaternion.
randar::Quaternion randar::Rotation::getQuaternion() const
{
    return this->quaternion;
}

// Retrieves quaternion matrix.
glm::mat4 randar::Rotation::getMatrix() const
{
    return this->quaternion.getMatrix();
}

// Convert to quaternion.
randar::Rotation::operator randar::Quaternion() const
{
    return this->getQuaternion();
}

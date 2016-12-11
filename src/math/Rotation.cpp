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

// Constructor, given an axis and angle.
randar::Rotation::Rotation(randar::Vector newAxis, randar::Angle newAngle)
{
    this->set(newAxis, newAngle);
}

// Sets the quaternion based on the axis and angle.
void randar::Rotation::updateQuaternion()
{
    float halfRads = this->angle.toRadians() / 2;
    Vector transformedAxis = this->axis * std::sin(halfRads);

    this->quaternion.w = std::cos(halfRads);
    this->quaternion.x = transformedAxis.x;
    this->quaternion.y = transformedAxis.y;
    this->quaternion.z = transformedAxis.z;
    this->quaternion.normalize();
}

// Updates the axis and angle described by the quaternion.
void randar::Rotation::readQuaternion()
{
    float halfRads = std::acos(this->quaternion.w);
    this->angle = halfRads * 2.0f;

    float sin = std::sin(halfRads);
    this->axis.x = this->quaternion.x / sin;
    this->axis.y = this->quaternion.y / sin;
    this->axis.z = this->quaternion.z / sin;
}

// Sets the axis and angle.
void randar::Rotation::set(randar::Vector newAxis, randar::Angle newAngle)
{
    newAxis.normalize();
    this->axis = newAxis;
    this->angle = newAngle;
    this->updateQuaternion();
}

// Sets and retrieves axis.
void randar::Rotation::setAxis(randar::Vector newAxis)
{
    this->set(newAxis, this->angle);
}

randar::Vector randar::Rotation::getAxis() const
{
    return this->axis;
}

// Sets and retrieves angle.
void randar::Rotation::setAngle(randar::Angle newAngle)
{
    this->set(this->axis, newAngle);
}

void randar::Rotation::rotate(randar::Angle deltaAngle)
{
    this->setAngle(this->angle + deltaAngle);
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

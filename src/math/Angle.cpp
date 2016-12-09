#include <randar/math/Angle.hpp>

randar::Angle::Angle(float newRadians)
{
    (*this) = newRadians;
}

float randar::Angle::toRadians() const
{
    return this->radians;
}

randar::Angle& randar::Angle::operator =(float newRadians)
{
    this->radians = newRadians;
    return *this;
}

randar::Angle::operator float() const
{
    return this->toRadians();
}

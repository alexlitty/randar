#include <randar/math/Angle.hpp>

randar::Angle::Angle(float newRadians)
{
    (*this) = newRadians;
}

randar::Angle& randar::Angle::operator =(float newRadians)
{
    this->radians = newRadians;
    return *this;
}

randar::Angle::operator float()
{
    return this->radians;
}

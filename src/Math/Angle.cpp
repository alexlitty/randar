#include <randar/Math/Angle.hpp>

randar::Angle::Angle(float newRadians)
{
    this->setRadians(newRadians);
}

void randar::Angle::setRadians(float newRadians)
{
    // Reduce redundant values.
    if (newRadians < 0.0f || newRadians >= TWO_PI) {
         newRadians = std::fmod((newRadians + TWO_PI), TWO_PI);
    }

    this->radians = newRadians;
}

float randar::Angle::toRadians() const
{
    return this->radians;
}

// Assignment and conversion operators.
randar::Angle& randar::Angle::operator =(float newRadians)
{
    this->setRadians(newRadians);
    return *this;
}

randar::Angle::operator float() const
{
    return this->toRadians();
}

// Addition operators.
randar::Angle& randar::Angle::operator +=(const randar::Angle& other)
{
    this->setRadians(this->toRadians() + other.toRadians());
    return *this;
}

randar::Angle randar::operator +(randar::Angle lhs, const randar::Angle& rhs)
{
    return lhs += rhs;
}

// Subtraction operators.
randar::Angle& randar::Angle::operator -=(const randar::Angle& other)
{
    this->setRadians(this->toRadians() - other.toRadians());
    return *this;
}

randar::Angle randar::operator -(randar::Angle lhs, const randar::Angle& rhs)
{
    return lhs -= rhs;
}

// Multiplication operators.
randar::Angle& randar::Angle::operator *=(float other)
{
    this->setRadians(this->toRadians() * other);
    return *this;
}

randar::Angle randar::operator *(randar::Angle lhs, float rhs)
{
    return lhs *= rhs;
}

// Division operators.
randar::Angle& randar::Angle::operator /=(float other)
{
    this->setRadians(this->toRadians() / other);
    return *this;
}

randar::Angle randar::operator /(randar::Angle lhs, float rhs)
{
    return lhs /= rhs;
}

#include <randar/math/Vector.hpp>

randar::Vector::Vector()
: randar::Vector::Vector(0.0f, 0.0f, 0.0f)
{

}

randar::Vector::Vector(float xInit, float yInit, float zInit)
: x(xInit),
  y(yInit),
  z(zInit)
{

}

// Convert to string.
std::string randar::Vector::toString() const
{
    return "("
         + std::to_string(x) + ", "
         + std::to_string(y) + ", "
         + std::to_string(z) + ")";
}

randar::Vector::operator std::string() const
{
    return this->toString();
}

// Addition operators.
randar::Vector& randar::Vector::operator +=(const Vector& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

randar::Vector randar::operator +(randar::Vector lhs, const randar::Vector& rhs)
{
    return lhs += rhs;
}

// Subtraction operators.
randar::Vector& randar::Vector::operator -=(const randar::Vector& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

randar::Vector randar::operator -(randar::Vector lhs, const randar::Vector& rhs)
{
    return lhs -= rhs;
}

// Multiplication operators.
randar::Vector& randar::Vector::operator *=(float other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

randar::Vector randar::operator *(randar::Vector lhs, float rhs)
{
    return lhs *= rhs;
}

// Division operators.
randar::Vector& randar::Vector::operator /=(float other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

randar::Vector randar::operator /(randar::Vector lhs, float rhs)
{
    return lhs /= rhs;
}

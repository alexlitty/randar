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

void randar::Vector::set(float xNew, float yNew, float zNew)
{
    this->x = xNew;
    this->y = yNew;
    this->z = zNew;
}

// Transforms this vector.
void randar::Vector::transform(const glm::mat4& matrix)
{
    glm::vec4 result(this->x, this->y, this->z, 1.0f);
    result = matrix * result;
    this->set(result.x, result.y, result.z);
}

// Transformation operators.
randar::Vector& randar::Vector::operator *=(const glm::mat4& matrix)
{
    this->transform(matrix);
    return *this;
}

randar::Vector randar::operator *(randar::Vector vector, const glm::mat4& matrix)
{
    return vector *= matrix;
}

randar::Vector randar::operator *(const glm::mat4& matrix, randar::Vector vector)
{
    return vector * matrix;
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

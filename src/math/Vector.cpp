#include <randar/math/Vector.hpp>

randar::Vector::Vector()
: randar::Vector::Vector(0.0f, 0.0f, 0.0f)
{

}

randar::Vector::Vector(btVector3 other)
: x(other.x()),
  y(other.y()),
  z(other.z())
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

// Normalizes this vector.
void randar::Vector::normalize()
{
    float magnitude = this->getMagnitude();
    if (!magnitude) {
        this->x = this->y = this->z = 0.0f;
    }
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

randar::Vector randar::Vector::normalized() const
{
    Vector result(*this);
    result.normalize();
    return result;
}

// Calculates the magnitude of this vector.
float randar::Vector::getMagnitude() const
{
    return std::sqrt(
          (this->x * this->x)
        + (this->y * this->y)
        + (this->z * this->z)
    );
}

// Dot and cross products.
float randar::Vector::dot(randar::Vector other) const
{
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

randar::Vector randar::Vector::cross(randar::Vector other) const
{
    other.set(
        (this->y * other.z) - (this->z * other.y),
        (this->z * other.x) - (this->x * other.z),
        (this->x * other.y) - (this->y * other.x)
    );

    return other;
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

randar::Vector randar::operator *(float lhs, randar::Vector rhs)
{
    return rhs * lhs;
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

// Convert to physics vector.
randar::Vector::operator btVector3() const
{
    return btVector3(this->x, this->y, this->z);
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

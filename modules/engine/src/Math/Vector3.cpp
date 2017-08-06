#include <randar/Math/Vector3.hpp>

randar::Vector3::Vector3()
: randar::Vector3::Vector3(0.0f, 0.0f, 0.0f)
{

}

randar::Vector3::Vector3(const btVector3& other)
: x(other.x()),
  y(other.y()),
  z(other.z())
{

}

randar::Vector3::Vector3(float xInit, float yInit, float zInit)
: x(xInit),
  y(yInit),
  z(zInit)
{

}

void randar::Vector3::set(float xNew, float yNew, float zNew)
{
    this->x = xNew;
    this->y = yNew;
    this->z = zNew;
}

// Normalizes this vector.
void randar::Vector3::normalize()
{
    float magnitude = this->getMagnitude();
    if (!magnitude) {
        this->x = this->y = this->z = 0.0f;
    }
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

randar::Vector3 randar::Vector3::normalized() const
{
    Vector3 result(*this);
    result.normalize();
    return result;
}

// Calculates the magnitude of this vector.
float randar::Vector3::getMagnitude() const
{
    return std::sqrt(
          (this->x * this->x)
        + (this->y * this->y)
        + (this->z * this->z)
    );
}

// Dot and cross products.
float randar::Vector3::dot(randar::Vector3 other) const
{
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

randar::Vector3 randar::Vector3::cross(randar::Vector3 other) const
{
    other.set(
        (this->y * other.z) - (this->z * other.y),
        (this->z * other.x) - (this->x * other.z),
        (this->x * other.y) - (this->y * other.x)
    );

    return other;
}

// Transforms this vector.
void randar::Vector3::transform(const glm::mat4& matrix)
{
    glm::vec4 result(this->x, this->y, this->z, 1.0f);
    result = matrix * result;
    this->set(result.x, result.y, result.z);
}

// Transformation operators.
randar::Vector3& randar::Vector3::operator *=(const glm::mat4& matrix)
{
    this->transform(matrix);
    return *this;
}

randar::Vector3 randar::operator *(randar::Vector3 vector, const glm::mat4& matrix)
{
    return vector *= matrix;
}

randar::Vector3 randar::operator *(const glm::mat4& matrix, randar::Vector3 vector)
{
    return vector * matrix;
}

// Basic arithmetic methods.
randar::Vector3 randar::Vector3::plus(randar::Vector3 other)
{
    return (other += *this);
}

randar::Vector3 randar::Vector3::minus(randar::Vector3 other)
{
    return (other -= *this);
}

randar::Vector3 randar::Vector3::times(float other)
{
    return (*this * other);
}

randar::Vector3 randar::Vector3::dividedBy(float other)
{
    return (*this / other);
}

// Addition operators.
randar::Vector3& randar::Vector3::operator +=(const Vector3& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

randar::Vector3 randar::operator +(randar::Vector3 lhs, const randar::Vector3& rhs)
{
    return lhs += rhs;
}

// Subtraction operators.
randar::Vector3& randar::Vector3::operator -=(const randar::Vector3& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

randar::Vector3 randar::operator -(randar::Vector3 lhs, const randar::Vector3& rhs)
{
    return lhs -= rhs;
}

// Multiplication operators.
randar::Vector3& randar::Vector3::operator *=(float other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

randar::Vector3 randar::operator *(randar::Vector3 lhs, float rhs)
{
    return lhs *= rhs;
}

randar::Vector3 randar::operator *(float lhs, randar::Vector3 rhs)
{
    return rhs * lhs;
}

// Division operators.
randar::Vector3& randar::Vector3::operator /=(float other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

randar::Vector3 randar::operator /(randar::Vector3 lhs, float rhs)
{
    return lhs /= rhs;
}

// Vector3 comparison operator.
bool randar::operator ==(const randar::Vector3& a, const Vector3& b)
{
    return a.x == b.x
        && a.y == b.y
        && a.z == b.z;
}

// Convert to physics vector.
randar::Vector3::operator btVector3() const
{
    return btVector3(this->x, this->y, this->z);
}

// Convert to string.
std::string randar::Vector3::toString() const
{
    return "("
         + std::to_string(x) + ", "
         + std::to_string(y) + ", "
         + std::to_string(z) + ")";
}

randar::Vector3::operator std::string() const
{
    return this->toString();
}

// Convert to JSON.
Json randar::Vector3::toJson() const
{
    return {
        { "x", this->x },
        { "y", this->y },
        { "z", this->z }
    };
}

// Node.js helpers for intuitive vector creation.
randar::Vector3 randar::vector()
{
    return Vector3();
}

randar::Vector3 randar::vector(float x, float y, float z)
{
    return Vector3(x, y, z);
}

randar::Vector3 randar::position()
{
    return randar::vector();
}

randar::Vector3 randar::position(float x, float y, float z)
{
    return randar::vector(x, y, z);
}

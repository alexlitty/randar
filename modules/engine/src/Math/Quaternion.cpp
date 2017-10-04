#include <randar/Math/Quaternion.hpp>

// Default construction.
randar::Quaternion::Quaternion()
: x(0.0f),
  y(0.0f),
  z(0.0f),
  w(1.0f)
{

}

// Construction from raw values.
randar::Quaternion::Quaternion(float ix, float iy, float iz, float iw)
{
    this->set(ix, iy, iz, iw);
}

// Construction from axis and angle.
randar::Quaternion::Quaternion(const Vector3& newAxis, const Angle& newAngle)
{
    this->set(newAxis, newAngle);
}

// Construction from physics quaternion.
randar::Quaternion::Quaternion(const btQuaternion& other)
{
    this->set(other.getAxis(), other.getAngle());
}

// Absolutely sets the rotation represented by this quaternion.
void randar::Quaternion::set(float ix, float iy, float iz, float iw)
{
    this->x = ix;
    this->y = iy;
    this->z = iz;
    this->w = iw;
    this->normalize();
}

void randar::Quaternion::set(const Vector3& newAxis, const Angle& newAngle)
{
    if (!newAxis.getMagnitude()) {
        throw std::runtime_error("Invalid axis");
    }

    Vector3 normalizedNewAxis = newAxis.normalized();

    float halfRads = newAngle.toRadians() / 2.0f;
    Vector3 transformedAxis = normalizedNewAxis * std::sin(halfRads);
    this->set(
        transformedAxis.x,
        transformedAxis.y,
        transformedAxis.z,
        std::cos(halfRads)
    );

    this->ax = normalizedNewAxis;
    this->ang = newAngle;
}

void randar::Quaternion::axis(const Vector3& newAxis)
{
    this->set(newAxis, this->angle());
}

void randar::Quaternion::angle(const Angle& newAngle)
{
    this->set(this->axis(), newAngle);
}

// Relatively sets the rotation represented by this quaternion.
void randar::Quaternion::rotate(const Angle& deltaAngle)
{
    this->angle(this->angle() + deltaAngle);
}

// Gets information about the represented rotation.
randar::Vector3 randar::Quaternion::axis() const
{
    return this->ax;
}

randar::Angle randar::Quaternion::angle() const
{
    return this->ang;
}

// Calculates the axis and angle from the x, y, z, and w components.
// @todo - use!
/*void randar::Quaternion::recompute()
{
    float denom = std::sin(this->angle().toRadians() / 2.0f);
    if (!denom) {
        this->ax.set(0, 0, 0);
    }
    this->ax = Vector3(this->x, this->y, this->z) / denom;
    this->ang = 2.0f * std::acos(this->w);
}*/

// Converts this quaternion to a unit quaternion.
void randar::Quaternion::normalize()
{
    float magnitude = std::sqrt((x*x) + (y*y) + (z*z) + (w*w));

    if (magnitude == 0.0f) {
        this->x = this->y = this->z = 0.0f;
        this->w = 1.0f;
    }

    else {
        this->x /= magnitude;
        this->y /= magnitude;
        this->z /= magnitude;
        this->w /= magnitude;
    }
}

// Transforms a single point.
randar::Vector3 randar::Quaternion::transform(randar::Vector3 vector) const
{
    return vector *= this->matrix();
}

// Retrieves a matrix for transforming.
glm::mat4 randar::Quaternion::matrix() const
{
    float values[16] = {
        1-2*y*y-2*z*z, 2*x*y - 2*z*w, 2*x*z + 2*y*w, 0,
        2*x*y + 2*z*w, 1-2*x*x-2*z*z, 2*y*z - 2*x*w, 0,
        2*x*z - 2*y*w, 2*y*z + 2*x*w, 1-2*x*x-2*y*y, 0,
        0, 0, 0, 1
    };

    return glm::make_mat4(values);
}

// Combination operators.
randar::Quaternion& randar::Quaternion::operator *=(const Quaternion& other)
{
    this->set(
        (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y),
        (this->w * other.y) - (this->x * other.z) + (this->y * other.w) + (this->z * other.x),
        (this->w * other.z) + (this->x * other.y) - (this->y * other.x) + (this->z * other.w),
        (this->w * other.w) - (this->x * other.x) - (this->y * other.y) - (this->z * other.z)
    );

    return *this;
}

randar::Quaternion randar::operator *(randar::Quaternion lhs, const randar::Quaternion& rhs)
{
    return lhs *= rhs;
}

// Converts to physics quaternion.
randar::Quaternion::operator btQuaternion() const
{
    return btQuaternion(this->x, this->y, this->z, this->w);
}

// Node.js helpers.
randar::Quaternion randar::quaternion()
{
    return randar::Quaternion();
}

randar::Quaternion randar::quaternion(const randar::Vector3& axis, const randar::Angle& angle)
{
    return randar::Quaternion(axis, angle);
}

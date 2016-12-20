#include <randar/math/Quaternion.hpp>

// Default construction.
randar::Quaternion::Quaternion()
: w(1.0f)
{

}

// Construction from raw values.
randar::Quaternion::Quaternion(float ix, float iy, float iz, float iw)
{
    this->set(ix, iy, iz, iw);
}

// Construction from axis and angle.
randar::Quaternion::Quaternion(const Vector& newAxis, const Angle& newAngle)
{
    this->set(newAxis, newAngle);
}

// Construction from physics quaternion.
randar::Quaternion::Quaternion(const btQuaternion& other)
{
    this->set(other.getAxis(), other.getAngle());
}

// Absolutely sets the rotation represented by this quaternion.
void randar::Quaternion::set(float ix, float iy, float iz, float iw, bool updateAxis)
{
    this->x = ix;
    this->y = iy;
    this->z = iz;
    this->w = iw;
    this->normalize();

    if (updateAxis) {
        this->axis = this->getAxis();
    }
}

void randar::Quaternion::set(const Vector& newAxis, const Angle& newAngle)
{
    float halfRads = newAngle.toRadians() / 2.0f;
    Vector transformedAxis = newAxis.normalized() * std::sin(halfRads);
    this->set(
        transformedAxis.x,
        transformedAxis.y,
        transformedAxis.z,
        std::cos(halfRads),
        false
    );

    this->axis = newAxis;
}

void randar::Quaternion::setAxis(const Vector& newAxis)
{
    this->set(newAxis, this->getAngle());
}

void randar::Quaternion::setAngle(const Angle& newAngle)
{
    this->set(this->axis, newAngle);
}

// Relatively sets the rotation represented by this quaternion.
void randar::Quaternion::rotate(const Angle& deltaAngle)
{
    this->setAngle(this->getAngle() + deltaAngle);
}

// Gets information about the represented rotation.
randar::Vector randar::Quaternion::getAxis() const
{
    float d = std::sqrt(1 - (this->w * this->w));

    // Arbitrary axis. Any axis produces the same result.
    if (d == 0.0f) {
        return Vector(1.0f, 0.0f, 0.0f);
    }

    return Vector(
        this->x / d,
        this->y / d,
        this->z / d
    ).normalized();
}

randar::Angle randar::Quaternion::getAngle() const
{
    return 2.0f * std::acos(this->w);
}

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
randar::Vector randar::Quaternion::transform(randar::Vector vector) const
{
    return vector *= this->getMatrix();
}

// Retrieves a matrix for transforming.
glm::mat4 randar::Quaternion::getMatrix() const
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

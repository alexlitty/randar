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
randar::Quaternion::Quaternion(const Vector& axis, const Angle& angle)
{
    this->set(axis, angle);
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

void randar::Quaternion::set(const Vector& axis, const Angle& angle)
{
    float halfRads = angle.toRadians() / 2.0f;
    Vector transformedAxis = axis * std::sin(halfRads);
    this->set(
        transformedAxis.x,
        transformedAxis.y,
        transformedAxis.z,
        std::cos(halfRads)
    );
}

void randar::Quaternion::setAxis(const Vector& axis)
{
    this->set(axis, this->getAngle());
}

void randar::Quaternion::setAngle(const Angle& angle)
{
    this->set(this->getAxis(), angle);
}

// Relatively sets the rotation represented by this quaternion.
void randar::Quaternion::rotate(const Angle& angle)
{
    this->setAngle(this->getAngle() + angle);
}

// Gets information about the represented rotation.
randar::Vector randar::Quaternion::getAxis() const
{
    float d = std::sqrt(1 - (this->w * this->w));

    // Arbitrary axis. Any axis produces the same result.
    if (d == 0.0f) {
        return Vector(0.0f, 0.0f, 0.0f);
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
    float magnitude = std::sqrt((w*w) + (x*x) + (y*y) + (z*z));
    if (magnitude == 0.0f) {
        this->w = this->x = this->y = this->z = 0.0f;
    }
    this->w /= magnitude;
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

// Transforms a single point.
randar::Vector randar::Quaternion::transform(randar::Vector vector) const
{
    return vector *= this->getMatrix();
}

// Retrieves a matrix for transforming.
glm::mat4 randar::Quaternion::getMatrix() const
{
    float w2 = w * w;
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;

    float twoXY = 2 * x * y;
    float twoXZ = 2 * x * z;
    float twoYZ = 2 * y * z;
    float twoWZ = 2 * w * z;
    float twoWX = 2 * w * x;
    float twoWY = 2 * w * y;

    float values[16] = {
        w2 + x2 - y2 - z2, twoXY - twoWZ    , twoXZ + twoWY    , 0,
        twoXY + twoWZ    , w2 - x2 + y2 - z2, twoYZ + twoWX    , 0,
        twoXZ - twoWY    , twoYZ - twoWX    , w2 - x2 - y2 + z2, 0,
        0                , 0                , 0                , 1
    };

    return glm::make_mat4(values);
}

// Combination operators.
randar::Quaternion& randar::Quaternion::operator *=(const Quaternion& other)
{
    this->w = (this->w * other.w) - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
    this->x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
    this->y = (this->w * other.y) - (this->x * other.z) + (this->y * other.w) + (this->z * other.x);
    this->z = (this->w * other.z) + (this->x * other.y) - (this->y * other.x) + (this->z * other.w);
    normalize();

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

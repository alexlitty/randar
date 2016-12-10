#include <randar/math/Quaternion.hpp>

randar::Quaternion::Quaternion()
: w(1.0f)
{

}

void randar::Quaternion::normalize()
{
    float magnitude = std::sqrt((w*w) + (x*x) + (y*y) + (z*z));
    this->w /= magnitude;
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

glm::mat4 randar::Quaternion::getMatrix() const
{
    float twoXSquared = 2 * (x * x);
    float twoYSquared = 2 * (y * y);
    float twoZSquared = 2 * (z * z);

    float twoXY = 2 * x * y;
    float twoXZ = 2 * x * z;
    float twoYZ = 2 * y * z;
    float twoWZ = 2 * w * z;
    float twoWX = 2 * w * x;
    float twoWY = 2 * w * y;

    float values[16] = {
        1 - twoYSquared - twoZSquared, twoXY - twoWZ                , twoXZ + twoWY                , 0,
        twoXY + twoWZ                , 1 - twoXSquared - twoZSquared, twoYZ + twoWX                , 0,
        twoXZ - twoWY                , twoYZ - twoWX                , 1 - twoXSquared - twoYSquared, 0,
        0                            , 0                            , 0                            , 1
    };

    return glm::make_mat4(values);
}

randar::Quaternion& randar::Quaternion::operator *=(const Quaternion& other)
{
    this->w = (this->w * other.w) - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
    this->x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
    this->y = (this->w * other.y) - (this->x * other.z) + (this->y * other.w) + (this->z * other.x);
    this->z = (this->w * other.z) + (this->x * other.y) - (this->y * other.x) + (this->z * other.w);
    normalize();

    return *this;
}

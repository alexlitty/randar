#ifndef RANDAR_MATH_QUATERNION_HPP
#define RANDAR_MATH_QUATERNION_HPP

#include <cmath>
#include <randar/utility/glm.hpp>

namespace randar
{
    struct Quaternion
    {
        float w;
        float x;
        float y;
        float z;

        Quaternion();

        void normalize();
        glm::mat4 getMatrix() const;

        Quaternion& operator *=(const Quaternion& other);
    };

    Quaternion operator *(Quaternion lhs, const Quaternion& rhs);
}

#endif

#ifndef RANDAR_MATH_QUATERNION_HPP
#define RANDAR_MATH_QUATERNION_HPP

#include <cmath>
#include <randar/math/Vector.hpp>
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

        /**
         * Converts this quaternion to a unit quaternion.
         */
        void normalize();

        /**
         * Transforms a vector.
         */
        Vector transform(Vector vector) const;

        /**
         * Retrieves a matrix for transforming.
         */
        glm::mat4 getMatrix() const;

        /**
         * Combination assignment operator.
         */
        Quaternion& operator *=(const Quaternion& other);
    };

    /**
     * Combination operator.
     */
    Quaternion operator *(Quaternion lhs, const Quaternion& rhs);

    /**
     * Transformation operators.
     */
    Vector operator *(const Quaternion& quaternion, Vector vector);
    Vector operator *(Vector vector, const Quaternion& quaternion);
}

#endif

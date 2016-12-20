#ifndef RANDAR_MATH_QUATERNION_HPP
#define RANDAR_MATH_QUATERNION_HPP

#include <cmath>
#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/math/Angle.hpp>
#include <randar/math/Vector.hpp>
#include <randar/utility/glm.hpp>

namespace randar
{
    struct Quaternion
    {
        float x;
        float y;
        float z;
        float w;

        /**
         * Default construction.
         */
        Quaternion();

        /**
         * Construction from raw values.
         */
        Quaternion(float ix, float iy, float iz, float iw);

        /**
         * Construction from axis and angle.
         */
        Quaternion(const Vector& axis, const Angle& angle);

        /**
         * Construction from physics quaternion.
         */
        Quaternion(const btQuaternion& other);

        /**
         * Absolutely sets the rotation represented by this quaternion.
         */
        void set(float ix, float iy, float iz, float iw);
        void set(const Vector& axis, const Angle& angle);
        void setAxis(const Vector& axis);
        void setAngle(const Angle& angle);

        /**
         * Relatively sets the rotation represented by this quaternion.
         */
        void rotate(const Angle& angle);

        /**
         * Gets information about the represented rotation.
         */
        Vector getAxis() const;
        Angle getAngle() const;

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

        /**
         * Converts to physics quaternion.
         */
        operator btQuaternion() const;
    };

    /**
     * Combination operator.
     */
    Quaternion operator *(Quaternion lhs, const Quaternion& rhs);
}

#endif

#ifndef RANDAR_MATH_QUATERNION_HPP
#define RANDAR_MATH_QUATERNION_HPP

#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/Math/Angle.hpp>
#include <randar/Math/Vector3.hpp>
#include <randar/Utility/glm.hpp>
#include <randar/Utility/Json.hpp>

namespace randar
{
    class Quaternion
    {
        float x;
        float y;
        float z;
        float w;

        Vector3 axis;

    public:
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
        Quaternion(const Vector3& newAxis, const Angle& newAngle);

        /**
         * Construction from physics quaternion.
         */
        Quaternion(const btQuaternion& other);

        /**
         * Absolutely sets the rotation represented by this quaternion.
         */
        void set(float ix, float iy, float iz, float iw, bool updateAxis = true);
        void set(const Vector3& newAxis, const Angle& newAngle);
        void setAxis(const Vector3& newAxis);
        void setAngle(const Angle& newAngle);

        /**
         * Relatively sets the rotation represented by this quaternion.
         */
        void rotate(const Angle& newAngle);

        /**
         * Gets information about the represented rotation.
         */
        Vector3 getAxis() const;
        Angle getAngle() const;

        /**
         * Converts this quaternion to a unit quaternion.
         */
        void normalize();

        /**
         * Transforms a vector.
         */
        Vector3 transform(Vector3 vector) const;

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

        /**
         * Converts to JSON.
         */
        Json toJson() const;
    };

    /**
     * Combination operator.
     */
    Quaternion operator *(Quaternion lhs, const Quaternion& rhs);
}

#endif

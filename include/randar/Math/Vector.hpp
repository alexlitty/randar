#ifndef RANDAR_MATH_VECTOR_HPP
#define RANDAR_MATH_VECTOR_HPP

#include <string>
#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/Utility/glm.hpp>
#include <randar/Utility/Json.hpp>

namespace randar
{
    struct Vector
    {
        float x;
        float y;
        float z;

        Vector();
        Vector(const btVector3& other);
        Vector(float xInit, float yInit, float zInit = 0.0f);
        void set(float xNew, float yNew, float zNew = 0.0f);

        /**
         * Normalizes this vector.
         */
        void normalize();
        Vector normalized() const;

        /**
         * Calculates the magnitude of this vector.
         */
        float getMagnitude() const;

        /**
         * Dot and cross products.
         */
        float dot(Vector other) const;
        Vector cross(Vector other) const;

        /**
         * Transforms this vector.
         */
        void transform(const glm::mat4& matrix);

        /**
         * Transformation assignment operator.
         */
        Vector& operator *=(const glm::mat4& matrix);

        /**
         * Mathematical assignment operators.
         */
        Vector& operator +=(const Vector& other);
        Vector& operator -=(const Vector& other);
        Vector& operator *=(float other);
        Vector& operator /=(float other);

        /**
         * Convert to physics vector.
         */
        operator btVector3() const;

        /**
         * Convert to string.
         */
        std::string toString() const;
        operator std::string() const;

        /**
         * Convert to JSON.
         */
        Json toJson() const;
    };

    /**
     * Transformation operators.
     */
    Vector operator *(Vector vector, const glm::mat4& matrix);
    Vector operator *(const glm::mat4& matrix, Vector vector);

    /**
     * Mathematical operators.
     */
    Vector operator +(Vector lhs, const Vector& rhs);
    Vector operator -(Vector lhs, const Vector& rhs);
    Vector operator *(Vector lhs, float rhs);
    Vector operator *(float lhs, Vector rhs);
    Vector operator /(Vector lhs, float other);
}

#endif

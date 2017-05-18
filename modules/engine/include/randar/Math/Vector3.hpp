#ifndef RANDAR_MATH_VECTOR_HPP
#define RANDAR_MATH_VECTOR_HPP

#include <string>
#include <bullet3/btBulletDynamicsCommon.h>
#include <randar/Utility/glm.hpp>
#include <randar/Utility/Json.hpp>

namespace randar
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3();
        Vector3(const btVector3& other);
        Vector3(float xInit, float yInit, float zInit = 0.0f);
        void set(float xNew, float yNew, float zNew = 0.0f);

        /**
         * Normalizes this vector.
         */
        void normalize();
        Vector3 normalized() const;

        /**
         * Calculates the magnitude of this vector.
         */
        float getMagnitude() const;

        /**
         * Dot and cross products.
         */
        float dot(Vector3 other) const;
        Vector3 cross(Vector3 other) const;

        /**
         * Transforms this vector.
         */
        void transform(const glm::mat4& matrix);

        /**
         * Transformation assignment operator.
         */
        Vector3& operator *=(const glm::mat4& matrix);

        /**
         * Mathematical assignment operators.
         */
        Vector3& operator +=(const Vector3& other);
        Vector3& operator -=(const Vector3& other);
        Vector3& operator *=(float other);
        Vector3& operator /=(float other);

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
    Vector3 operator *(Vector3 vector, const glm::mat4& matrix);
    Vector3 operator *(const glm::mat4& matrix, Vector3 vector);

    /**
     * Mathematical operators.
     */
    Vector3 operator +(Vector3 lhs, const Vector3& rhs);
    Vector3 operator -(Vector3 lhs, const Vector3& rhs);
    Vector3 operator *(Vector3 lhs, float rhs);
    Vector3 operator *(float lhs, Vector3 rhs);
    Vector3 operator /(Vector3 lhs, float other);

    /**
     * Vector3 comparison operator.
     */
    bool operator ==(const Vector3& a, const Vector3& b);

    /**
     * Node.js helpers for intuitive vector creation.
     */
    Vector3 vector();
    Vector3 vector(float x, float y, float z = 0.0f);

    Vector3 position();
    Vector3 position(float x, float y, float z = 0.0f);
}

#endif

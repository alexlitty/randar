#ifndef RANDAR_MATH_VECTOR_HPP
#define RANDAR_MATH_VECTOR_HPP

#include <string>
#include <randar/utility/glm.hpp>

namespace randar
{
    struct Vector
    {
        float x;
        float y;
        float z;

        Vector();
        Vector(float xInit, float yInit, float zInit);
        void set(float xNew, float yNew, float zNew);

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
         * Convert to string.
         */
        std::string toString() const;
        operator std::string() const;
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
    Vector operator *(Vector lhs, float other);
    Vector operator /(Vector lhs, float other);
}

#endif

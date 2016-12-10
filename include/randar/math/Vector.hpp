#ifndef RANDAR_MATH_VECTOR_HPP
#define RANDAR_MATH_VECTOR_HPP

#include <string>

namespace randar
{
    struct Vector
    {
        float x;
        float y;
        float z;

        Vector();
        Vector(float xInit, float yInit, float zInit);

        /**
         * Convert to string.
         */
        std::string toString() const;
        operator std::string() const;

        /**
         * Mathematical assignment operators.
         */
        Vector& operator +=(const Vector& other);
        Vector& operator -=(const Vector& other);
        Vector& operator *=(float other);
        Vector& operator /=(float other);
    };

    /**
     * Mathematical operators.
     */
    Vector operator +(Vector lhs, const Vector& rhs);
    Vector operator -(Vector lhs, const Vector& rhs);
    Vector operator *(Vector lhs, float other);
    Vector operator /(Vector lhs, float other);
}

#endif

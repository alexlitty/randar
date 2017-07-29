#ifndef RANDAR_MATH_ANGLE_HPP
#define RANDAR_MATH_ANGLE_HPP

#include <randar/Math/Constant.hpp>

namespace randar
{
    class Angle
    {
        float radians;

    public:
        Angle(float newRadians = 0.0f);

        /**
         * Sets and gets the underlying angle value.
         *
         * Normalized into [0 - 2PI).
         */
        void setRadians(float newRadians);
        float toRadians() const;
        
        /**
         * Assignment and conversion operators.
         */
        Angle& operator =(float newRadians);
        operator float() const;

        /**
         * Mathematical assignment operators.
         */
        Angle& operator +=(const Angle& other);
        Angle& operator -=(const Angle& other);
        Angle& operator *=(float other);
        Angle& operator /=(float other);
    };

    /**
     * Mathematical operators.
     */
    Angle operator +(Angle lhs, const Angle& rhs);
    Angle operator -(Angle lhs, const Angle& rhs);
    Angle operator *(Angle lhs, float rhs);
    Angle operator /(Angle lhs, float rhs);

    /**
     * Node.js helper.
     */
    Angle angle(float radians = 0.0f);
}

#endif

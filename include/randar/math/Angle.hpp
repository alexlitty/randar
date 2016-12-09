#ifndef RANDAR_MATH_ANGLE_HPP
#define RANDAR_MATH_ANGLE_HPP

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
         * Mathematical operators.
         */
        Angle& operator +=(const Angle& other);
        Angle& operator -=(const Angle& other);
    };

    Angle operator +(Angle lhs, const Angle& rhs);
    Angle operator -(Angle lhs, const Angle& rhs);
}

#endif

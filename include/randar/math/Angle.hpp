#ifndef RANDAR_MATH_ANGLE_HPP
#define RANDAR_MATH_ANGLE_HPP

namespace randar
{
    class Angle
    {
        float radians;

    public:
        Angle(float newRadians = 0.0f);
        float toRadians() const;
        
        Angle& operator =(float newRadians);
        operator float() const;
    };
}

#endif

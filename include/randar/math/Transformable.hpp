#ifndef RANDAR_MATH_TRANSFORMABLE_HPP
#define RANDAR_MATH_TRANSFORMABLE_HPP

#include <randar/math/Angle.hpp>
#include <randar/math/Vector.hpp>

namespace randar
{
    class Transformable
    {
        Vector position;
        Angle angle;

    public:
        void setPosition(Vector newPosition);
        void move(Vector movement);
        Vector getPosition() const;

        void setAngle(Angle angle);
        Angle getAngle() const;
    };
}

#endif

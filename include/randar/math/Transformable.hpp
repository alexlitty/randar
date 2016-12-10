#ifndef RANDAR_MATH_TRANSFORMABLE_HPP
#define RANDAR_MATH_TRANSFORMABLE_HPP

#include <randar/math/Rotation.hpp>

namespace randar
{
    class Transformable
    {
    protected:
        Vector position;
        Rotation rotation;

    public:

        /**
         * Sets the position absolutely.
         */
        void setPosition(Vector newPosition);

        /**
         * Sets the position relatively.
         */
        void move(Vector movement);

        /**
         * Retrieves the position.
         */
        Vector getPosition() const;

        /**
         * Sets the rotation.
         */
        void setRotation(Rotation newRotation);

        /**
         * Sets the rotation, given an origin and angle.
         */
        void setRotation(Vector origin, Angle angle);

        /**
         * Retrieves the rotation.
         */
        Rotation getRotation() const;

        /**
         * Sets the origin of rotation.
         */
        void setRotationOrigin(Vector origin);

        /**
         * Retrieves the origin of rotation.
         */
        Vector getRotationOrigin() const;

        /**
         * Sets the rotation angle absolutely.
         */
        void setAngle(Angle angle);

        /**
         * Sets the rotation angle relatively.
         */
        void rotate(Angle angle);

        /**
         * Retrieves the rotation angle.
         */
        Angle getAngle() const;

        /**
         * Function called when a transformation occurs.
         */
        virtual void onTransform();
    };
}

#endif

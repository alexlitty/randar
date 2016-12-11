#ifndef RANDAR_MATH_ROTATION_HPP
#define RANDAR_MATH_ROTATION_HPP

#include <randar/math/Angle.hpp>
#include <randar/math/Quaternion.hpp>

namespace randar
{
    class Rotation
    {
        Quaternion quaternion;

        Vector origin;
        Angle angle;

        /**
         * Sets the quaternion based on the origin and angle.
         */
        void updateQuaternion();

        /**
         * Updates the origin and angle described by the quaternion.
         */
        void readQuaternion();

    public:
        /**
         * Default constructor.
         */
        Rotation();

        /**
         * Constructor, given a quaternion.
         */
        Rotation(const Quaternion& quaternion);

        /**
         * Constructor, given an origin and angle.
         */
        Rotation(Vector newOrigin, Angle newAngle);
        
        /**
         * Sets the origin and angle.
         *
         * More efficient than setting origin and angle separately.
         */
        void set(Vector newOrigin, Angle newAngle);

        /**
         * Sets and retrieves origin.
         */
        void setOrigin(Vector newOrigin);
        Vector getOrigin() const;

        /**
         * Sets and retrieves angle.
         */
        void setAngle(Angle newAngle);
        Angle getAngle() const;

        /**
         * Transforms a vector.
         */
        Vector transform(Vector vector) const;

        /**
         * Retrieves quaternion information.
         */
        Quaternion getQuaternion() const;
        glm::mat4 getMatrix() const;

        /**
         * Convert to quaternion.
         */
        operator Quaternion() const;
    };
}

#endif

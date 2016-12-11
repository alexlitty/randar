#ifndef RANDAR_MATH_ROTATION_HPP
#define RANDAR_MATH_ROTATION_HPP

#include <randar/math/Angle.hpp>
#include <randar/math/Quaternion.hpp>

namespace randar
{
    class Rotation
    {
        Quaternion quaternion;

        Vector axis;
        Angle angle;

        /**
         * Sets the quaternion based on the axis and angle.
         */
        void updateQuaternion();

        /**
         * Updates the axis and angle described by the quaternion.
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
         * Constructor, given an axis and angle.
         */
        Rotation(Vector newAxis, Angle newAngle);
        
        /**
         * Sets the axis and angle.
         *
         * More efficient than setting axis and angle separately.
         */
        void set(Vector newAxis, Angle newAngle);

        /**
         * Sets and retrieves axis.
         */
        void setAxis(Vector newAxis);
        Vector getAxis() const;

        /**
         * Sets and retrieves angle.
         */
        void setAngle(Angle newAngle);
        void rotate(Angle deltaAngle);
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

#ifndef RANDAR_MATH_TRANSFORMABLE_HPP
#define RANDAR_MATH_TRANSFORMABLE_HPP

#include <randar/math/Quaternion.hpp>

namespace randar
{
    class Transformable
    {
    protected:
        Vector position;
        Quaternion rotation;

    public:
        virtual ~Transformable();

        /**
         * Sets this transformation from a physical transformation.
         */
        void set(const btTransform& transform);

        /**
         * Absolutely sets the position.
         */
        void setPosition(const Vector& newPosition);

        /**
         * Relatively sets the position.
         */
        void move(const Vector& movement);
        void move(const Quaternion& angularMovement);

        /**
         * Retrieves the position.
         */
        Vector getPosition() const;

        /**
         * Sets the rotation.
         */
        void setRotation(const Quaternion& quaternion);
        void setRotation(const Vector& axis, const Angle& angle);

        /**
         * Retrieves the rotation.
         */
        Quaternion getRotation() const;

        /**
         * Sets and retrieves the axis of rotation.
         */
        void setRotationAxis(const Vector& axis);
        Vector getRotationAxis() const;

        /**
         * Absolutely sets the angle of rotation.
         */
        void setAngle(const Angle& angle);

        /**
         * Relatively sets the angle of rotation.
         */
        void rotate(const Angle& angle);

        /**
         * Retrieves the angle of rotation.
         */
        Angle getAngle() const;

        /**
         * Function called when a transformation occurs.
         */
        virtual void onTransform();

        /**
         * Retrieves the current transformation matrix.
         */
        glm::mat4 getTransformMatrix() const;

        /**
         * Converts to physics transformation.
         */
        operator btTransform() const;
    };
}

#endif

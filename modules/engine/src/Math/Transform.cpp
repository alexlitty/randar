#include <randar/Math/Transform.hpp>

// Constructors.
randar::Transform::Transform(
    const randar::Vector3& initPosition,
    const randar::Quaternion& initRotation
)
: pos(initPosition),
  rot(initRotation)
{

}

randar::Transform::Transform(
    const randar::Vector3& initPosition,
    const randar::Vector3& initAxis,
    const randar::Angle& initAngle
)
: randar::Transform(initPosition, randar::Quaternion(initAxis, initAngle))
{

}

randar::Transform::Transform(
    const randar::Quaternion& initRotation
)
: randar::Transform(randar::Vector3(), initRotation)
{

}

randar::Transform::Transform(
    const randar::Vector3& initAxis,
    const randar::Angle& initAngle
)
: randar::Transform(randar::Quaternion(initAxis, initAngle))
{

}

// Destructor.
randar::Transform::~Transform()
{

}

// Sets the transformation.
void randar::Transform::set(
    const randar::Vector3& newPosition,
    const randar::Quaternion& newRotation
)
{
    this->position(newPosition);
    this->rotation(newRotation);
}

void randar::Transform::set(
    const randar::Vector3& newPosition,
    const randar::Vector3& newAxis,
    const randar::Angle& newAngle
)
{
    this->set(newPosition, randar::Quaternion(newAxis, newAngle));
}

// Sets the transformation from a physical transformation.
void randar::Transform::set(const btTransform& transform)
{
    this->position(transform.getOrigin());
    this->rotation(transform.getRotation());
}

// Absolutely sets the position.
void randar::Transform::position(const randar::Vector3& newPosition)
{
    this->pos = newPosition;
}

// Relatively sets the position.
void randar::Transform::move(const randar::Vector3& movement)
{
    this->position(
        this->position() + movement
    );
}

void randar::Transform::move(const randar::Quaternion& angularMovement)
{
    this->position(
        angularMovement.transform(this->position())
    );
}

void randar::Transform::move(const randar::Vector3& axis, const Angle& angle)
{
    this->move(randar::Quaternion(axis, angle));
}

// Retrieves the position.
randar::Vector3 randar::Transform::position() const
{
    return this->pos;
}

// Sets the rotation.
void randar::Transform::rotation(const randar::Quaternion& quaternion)
{
    this->rot = quaternion;
}

void randar::Transform::rotation(const randar::Vector3& axis, const randar::Angle& angle)
{
    this->rot.set(axis, angle);
}

// Retrieves the rotation.
randar::Quaternion randar::Transform::rotation() const
{
    return this->rot;
}

// Sets and retrieves the axis of rotation.
void randar::Transform::axis(const randar::Vector3& newAxis)
{
    this->rotation().axis(newAxis);
}

randar::Vector3 randar::Transform::axis() const
{
    return this->rotation().axis();
}

// Absolutely sets the angle of rotation.
void randar::Transform::angle(const randar::Angle& angle)
{
    this->rotation().angle(angle);
}

// Relatively sets the angle of rotation.
void randar::Transform::rotate(const randar::Angle& angle)
{
    this->rotation().angle(this->rotation().angle() + angle);
}

// Retrieves the angle of rotation.
randar::Angle randar::Transform::angle() const
{
    return this->rotation().angle();
}

// Applies another transform to this transform.
void randar::Transform::apply(const randar::Transform& other)
{
    this->move(other.position());
    // @@@ - Also rotate
}

// Function called when a transformation occurs.
void randar::Transform::onTransform()
{

}

// Transforms a vector.
randar::Vector3 randar::Transform::transform(const randar::Vector3& vector) const
{
    return vector * this->transformMatrix();
}

// Retrieves the current transformation matrix.
glm::mat4 randar::Transform::transformMatrix() const
{
    glm::vec3 glmPosition(this->position().x, this->position().y, this->position().z);
    return glm::translate(this->rotation().matrix(), glmPosition);
}

// Converts to physics transformation.
randar::Transform::operator btTransform() const
{
    return btTransform(this->rotation(), this->position());
}

// An identity transformation.
randar::Transform randar::Transform::Identity;

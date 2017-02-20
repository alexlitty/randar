#include <randar/Scene/TransformState.hpp>

// Sets the transformation for this state.
void randar::TransformState::set(const Transform& other)
{
    this->transform = other;
}

// Applies this state to a transform.
void randar::TransformState::apply(Transform& other)
{
    other = this->transform;
}

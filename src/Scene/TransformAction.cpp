#include <randar/Scene/TransformAction.hpp>

// Constructor.
randar::TransformAction::TransformAction(
    const randar::FrameRange& frames,
    randar::Transform* initTarget)
: randar::Action("transform", frames),
  target(initTarget)
{

}

// Applies a single frame of this transformation to the target.
void randar::TransformAction::apply()
{
    this->target->apply(this->transform);
}

// Returns a representation of this transform action as JSON.
Json randar::TransformAction::toJson() const
{
    return this->transform.toJson();
}

#include <randar/Scene/Action.hpp>

// Constructor.
randar::Action::Action(
    const std::string& initType,
    const FrameRange& initFrames)
: type(initType),
  frames(initFrames)
{

}

// Destructor.
randar::Action::~Action()
{

}

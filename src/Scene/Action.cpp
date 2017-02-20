#include <randar/Scene/Action.hpp>

// Default constructor.
randar::Action::Action()
: type("invalid"),
  frames(0, 0)
{

}

// Constructor.
randar::Action::Action(
    const std::string& initType,
    const FrameRange& initFrames)
: type(initType),
  frames(initFrames)
{

}

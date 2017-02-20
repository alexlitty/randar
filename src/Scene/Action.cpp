#include <randar/Scene/Action.hpp>

randar::Action::Action(
    const std::string& initType,
    const FrameRange& initFrames)
: type(initType),
  frames(initFrames)
{

}

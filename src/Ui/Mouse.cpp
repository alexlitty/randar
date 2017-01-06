#include <randar/Ui/Mouse.hpp>

Awesomium::MouseButton randar::toAwesomium(randar::MouseButton button)
{
    switch (button) {
        case MouseButton::LEFT:
            return Awesomium::kMouseButton_Left;
        case MouseButton::MIDDLE:
            return Awesomium::kMouseButton_Middle;
        case MouseButton::RIGHT:
            return Awesomium::kMouseButton_Right;
        default:
            throw std::runtime_error("Converting invalid mouse button to Awesomium type");
    }
}

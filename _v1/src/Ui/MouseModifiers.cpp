#include <randar/Ui/MouseModifiers.hpp>

void randar::MouseModifiers::set(int modifiers)
{
    this->shift = modifiers && GLFW_MOD_SHIFT;
    this->control = modifiers && GLFW_MOD_CONTROL;
    this->alt = modifiers && GLFW_MOD_ALT;
}

#ifndef RANDAR_UI_MOUSE_MODIFIERS_HPP
#define RANDAR_UI_MOUSE_MODIFIERS_HPP

#include <randar/Engine/Glfw.hpp>

namespace randar
{
    struct MouseModifiers
    {
        bool shift = false;
        bool control = false;
        bool alt = false;

        void set(int modifiers);
    };
}

#endif

#ifndef RANDAR_UI_MOUSE_HPP
#define RANDAR_UI_MOUSE_HPP

#include <stdexcept>
#include <Awesomium/WebView.h>

namespace randar
{
    enum class MouseButton
    {
        LEFT,
        MIDDLE,
        RIGHT
    };

    Awesomium::MouseButton toAwesomium(randar::MouseButton button);
}

#endif

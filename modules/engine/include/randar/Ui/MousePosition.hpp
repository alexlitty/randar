#ifndef RANDAR_UI_MOUSE_POSITION_HPP
#define RANDAR_UI_MOUSE_POSITION_HPP

namespace randar
{
    /**
     * The position of a mouse relative to a window, where the top-left corner
     * of the window is (0, 0).
     */
    struct MousePosition
    {
        double x = 0;
        double y = 0;
    };
}

#endif

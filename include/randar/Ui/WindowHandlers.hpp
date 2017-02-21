#ifndef RANDAR_UI_WINDOW_HANDLERS_HPP
#define RANDAR_UI_WINDOW_HANDLERS_HPP

#include <randar/Ui/WindowListener.hpp>

namespace randar
{
    /**
     * Sends resize events to window listeners.
     */
    void onWindowResize(::GLFWwindow* window);
}

#endif

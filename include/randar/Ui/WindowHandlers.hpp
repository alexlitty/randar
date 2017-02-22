#ifndef RANDAR_UI_WINDOW_HANDLERS_HPP
#define RANDAR_UI_WINDOW_HANDLERS_HPP

#include <randar/Ui/WindowListener.hpp>

namespace randar
{
    /**
     * Registers a GLFW window for custom event handling.
     */
    void registerHandlers(::GLFWwindow* window);

    /**
     * Callback for GLFW resize events.
     *
     * Forwards the event to window listeners.
     */
    void onWindowResize(::GLFWwindow* window, int32_t width, int32_t height);
}

#endif

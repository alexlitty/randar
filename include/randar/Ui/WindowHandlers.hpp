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
     * Callback for GLFW window resize events.
     *
     * Forwards the event to window listeners.
     */
    void onWindowResize(::GLFWwindow* window, int32_t width, int32_t height);

    /**
     * Callback for GLFW mouse movement events.
     *
     * Forwards the event to window listeners.
     */
    void onMousePosition(::GLFWwindow* window, double x, double y);

    /**
     * Callback for GLFW mouse button events.
     *
     * Forwards the event to window listeners.
     */
    void onMouseButton(::GLFWwindow* window, int button, int actions, int mods);

    /**
     * Callback for GLFW scroll events.
     *
     * Forwards the event to window listeners.
     */
    void onScroll(::GLFWwindow* window, double x, double y);
}

#endif

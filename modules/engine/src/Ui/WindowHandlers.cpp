#include <randar/Ui/WindowHandlers.hpp>

// Registers a GLFW window for custom event handling.
void randar::registerHandlers(::GLFWwindow* window)
{
    ::glfwSetWindowSizeCallback(window, randar::onWindowResize);
    ::glfwSetCursorPosCallback(window, randar::onMousePosition);
    ::glfwSetMouseButtonCallback(window, randar::onMouseButton);
    ::glfwSetScrollCallback(window, randar::onScroll);
}

// Callback for GLFW window resize events.
void randar::onWindowResize(::GLFWwindow* window, int32_t width, int32_t height)
{
    for (auto listener : randar::WindowListener::list) {
        if (window == &listener->window) {
            listener->onResize(
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            );
        }
    }
}

// Callback for GLFW mouse movement events.
void randar::onMousePosition(::GLFWwindow* window, double x, double y)
{
    for (auto listener : randar::WindowListener::list) {
        if (window == &listener->window) {
            listener->onNativeMousePosition(x, y);
        }
    }
}

// Callback for GLFW mouse button events.
void randar::onMouseButton(::GLFWwindow* window, int button, int actions, int mods)
{
    for (auto listener : randar::WindowListener::list) {
        if (window == &listener->window) {
            listener->onNativeMouseButton(button, actions, mods);
        }
    }
}

// Callback for GLFW scroll events.
void randar::onScroll(::GLFWwindow* window, double x, double y)
{
    for (auto listener : randar::WindowListener::list) {
        if (window == &listener->window) {
            listener->onNativeScroll(x, y);
        }
    }
}

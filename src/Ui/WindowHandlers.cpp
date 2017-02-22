#include <randar/Ui/WindowHandlers.hpp>

// Registers a GLFW window for custom event handling.
void randar::registerHandlers(::GLFWwindow* window)
{
    ::glfwSetWindowSizeCallback(window, randar::onWindowResize);
}

// Sends resize events to window listeners.
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

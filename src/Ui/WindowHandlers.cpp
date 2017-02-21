#include <randar/Ui/WindowHandlers.hpp>

// Sends resize events to window listeners.
void onWindowResize(::GLFWwindow* window)
{
    int32_t width, height;
    ::glfwGetWindowSize(window, &width, &height);

    for (auto listener : randar::WindowListener::list) {
        if (window == &listener->window) {
            listener->onResize(
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            );
        }
    }
}

#include <randar/Engine/Native.hpp>

#ifdef __linux__
::Window randar::getNativeWindow(::GLFWwindow& window)
{
    return ::glfwGetX11Window(&window);
}
#endif

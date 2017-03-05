#include <randar/Engine/Native.hpp>

#if defined (__linux__)

::Window randar::getNativeWindow(::GLFWwindow& window)
{
    return ::glfwGetX11Window(&window);
}

#elif defined (_WIN32)

HWND randar::getNativeWindow(::GLFWwindow& window)
{
	return ::glfwGetWin32Window(&window);
}

#endif
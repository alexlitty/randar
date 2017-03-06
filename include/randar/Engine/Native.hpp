#ifndef RANDAR_ENGINE_NATIVE_WINDOW_HPP
#define RANDAR_ENGINE_NATIVE_WINDOW_HPP

#include <randar/Engine/Glfw.hpp>

namespace randar
{

#if defined (__linux__)
    ::Window getNativeWindow(::GLFWwindow& window);
#elif defined (_WIN32)
    HWND getNativeWindow(::GLFWwindow& window);
#endif

}

#endif

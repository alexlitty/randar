#ifndef RANDAR_ENGINE_NATIVE_WINDOW_HPP
#define RANDAR_ENGINE_NATIVE_WINDOW_HPP

#include <randar/Engine/Glfw.hpp>

namespace randar
{

#ifdef __linux__
    ::Window getNativeWindow(::GLFWwindow& window);
#endif

}

#endif

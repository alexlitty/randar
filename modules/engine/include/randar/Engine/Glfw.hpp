#ifndef RANDAR_UTILITY_GLFW_HPP
#define RANDAR_UTILITY_GLFW_HPP

#ifdef __linux__
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#elif __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#elif _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#endif

#ifndef RANDAR_UTILITY_GLFW_HPP
#define RANDAR_UTILITY_GLFW_HPP

#define GLFW_EXPOSE_NATIVE_GLX

#ifdef __linux__
#define GLFW_EXPOSE_NATIVE_X11
#elif __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#elif _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#endif

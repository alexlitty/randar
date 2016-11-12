#ifndef RANDAR_RANDAR_HPP
#define RANDAR_RANDAR_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace randar
{
    /**
     * A singleton object that bootstraps the Randar program.
     */
    class Randar
    {
        GLFWwindow *monitor;

    public:
        Randar();
        ~Randar();
    };
}

#endif

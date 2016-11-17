#ifndef RANDAR_RANDAR_HPP
#define RANDAR_RANDAR_HPP

#include <iostream>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <randar/Scene.hpp>

namespace randar
{
    /**
     * A singleton object that initializes the Randar engine.
     */
    class Randar
    {
        GLFWwindow *monitor;

    public:
        Randar();
        ~Randar();

        /**
         * List of scenes to render.
         */
        std::queue<Scene*> scenes;

        /**
         * Render the film.
         */
        void run();
    };
}

#endif

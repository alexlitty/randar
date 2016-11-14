#ifndef RANDAR_RANDAR_HPP
#define RANDAR_RANDAR_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
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
        std::vector<Scene*> scenes;

        /**
         * Render the film.
         */
        void run();
    };
}

#endif

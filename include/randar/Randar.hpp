#ifndef RANDAR_RANDAR_HPP
#define RANDAR_RANDAR_HPP

#include <iostream>
#include <queue>
#include <randar/engine/Window.hpp>
#include <randar/Scene.hpp>
#include <randar/Render.hpp>

namespace randar
{
    /**
     * A singleton object that initializes the Randar engine.
     */
    class Randar
    {
    public:
        Randar();

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

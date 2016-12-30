#ifndef RANDAR_SCENE_HPP
#define RANDAR_SCENE_HPP

#include <randar/Render/Camera.hpp>
#include <randar/Render/Light.hpp>
#include <randar/Utility/Resources.hpp>

namespace randar
{
    class Scene
    {
    protected:
        Color backgroundColor;
        Resources resources;
        Light light;

    public:
        virtual ~Scene();

        /**
         * Initializes the scene.
         */
        virtual void initialize() = 0;

        /**
         * Updates the scene for the next frame.
         *
         * Returns false if the scene is complete.
         */
        virtual bool update() = 0;

        /**
         * Draws all objects in the scene.
         */
        //virtual void draw(const Canvas& canvas) = 0;

        /**
         * Renders the entire scene frame.
         */
        void render();
    };
}

#endif

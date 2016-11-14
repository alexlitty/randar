#ifndef RANDAR_SCENE_HPP
#define RANDAR_SCENE_HPP

namespace randar
{
    class Scene
    {
    public:
        virtual ~Scene();

        /**
         * Updates the scene for the next frame.
         *
         * Returns false if the scene is complete.
         */
        virtual bool update() = 0;

        /**
         * Draws the scene.
         */
        virtual void draw() const = 0;
    };
}

#endif

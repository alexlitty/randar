#ifndef RANDAR_SCENE_HPP
#define RANDAR_SCENE_HPP

#include <randar/render/Canvas.hpp>
#include <randar/render/Drawable.hpp>

namespace randar
{
    class Scene : virtual public Canvas
    {
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
         * Renders the scene.
         */
        virtual void render() = 0;

        /**
         * Draw an object onto the scene.
         */
        //virtual void draw(randar::Drawable &drawable) const;

        /**
         * Draw vertices onto the scene.
         */
        virtual void draw(randar::Vertices &vertices, randar::RenderState state) const override;
    };
}

#endif

#ifndef RANDAR_SCENE_HPP
#define RANDAR_SCENE_HPP

#include <randar/render/Camera.hpp>
#include <randar/render/Canvas.hpp>
#include <randar/render/Drawable.hpp>
#include <randar/utility/Resources.hpp>

namespace randar
{
    class Scene : virtual public Canvas
    {
    protected:
        Resources resources;
        Camera camera;

    public:
        virtual ~Scene();

        /**
         * Initializes the scene.
         */
        virtual void initialize() = 0;

        /**
         * Clears the scene with a color.
         */
        virtual void clear(Color color) override;

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
         * Draw vertices onto the scene.
         */
        using Canvas::draw;
        virtual void draw(const randar::Vertices &vertices, randar::RenderState state) const override;
    };
}

#endif

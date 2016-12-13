#ifndef RANDAR_RENDER_CANVAS_HPP
#define RANDAR_RENDER_CANVAS_HPP

#include <randar/render/Camera.hpp>
#include <randar/render/Model.hpp>
#include <randar/render/ShaderProgram.hpp>

namespace randar
{
    /**
     * An object that may be drawn on.
     */
    class Canvas
    {
    protected:
        ShaderProgram *shaderProgram;
        Camera camera;

    public:
        virtual ~Canvas();
        void clear(Color color);

        void draw(const randar::Drawable& drawable) const;
    };
}

#endif

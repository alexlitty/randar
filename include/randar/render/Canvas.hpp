#ifndef RANDAR_RENDER_CANVAS_HPP
#define RANDAR_RENDER_CANVAS_HPP

#include <randar/render/RenderState.hpp>
#include <randar/render/Vertices.hpp>

namespace randar
{
    /**
     * An object that may be drawn on.
     */
    class Canvas
    {
    public:
        virtual ~Canvas();
        virtual void clear(Color color) = 0;
        virtual void draw(randar::Vertices &vertices, randar::RenderState state) const = 0;
    };
}

#endif

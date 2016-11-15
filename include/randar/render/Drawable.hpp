#ifndef RANDAR_RENDER_DRAWABLE_HPP
#define RANDAR_RENDER_DRAWABLE_HPP

#include <randar/render/Canvas.hpp>

namespace randar
{
    /**
     * An object that may be drawn to a canvas.
     */
    class Drawable
    {
    public:
        virtual ~Drawable();
        virtual void draw(randar::Canvas &canvas) const = 0;
    };
}

#endif

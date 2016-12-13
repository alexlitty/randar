#ifndef RANDAR_RENDER_DRAWABLE_HPP
#define RANDAR_RENDER_DRAWABLE_HPP

#include <randar/math/Transformable.hpp>

namespace randar
{
    /**
     * An object that may be drawn to a canvas.
     *
     * Drawing should only be invoked by a canvas.
     */
    class Drawable : virtual public Transformable
    {
    protected:

    public:
        virtual ~Drawable();
        virtual void draw() const = 0;
    };
}

#endif

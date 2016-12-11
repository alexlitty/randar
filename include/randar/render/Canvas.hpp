#ifndef RANDAR_RENDER_CANVAS_HPP
#define RANDAR_RENDER_CANVAS_HPP

#include <randar/render/Model.hpp>
#include <randar/render/RenderState.hpp>

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

        void draw(const randar::Model& model, randar::RenderState state) const;
        virtual void draw(const randar::Vertices& vertices, randar::RenderState state) const = 0;
    };
}

#endif

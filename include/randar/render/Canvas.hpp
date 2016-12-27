#ifndef RANDAR_RENDER_CANVAS_HPP
#define RANDAR_RENDER_CANVAS_HPP

#include <randar/engine/ResourceConsumer.hpp>
#include <randar/render/Camera.hpp>

namespace randar
{
    /**
     * An object that may be drawn on.
     */
    class Canvas : virtual public ResourceConsumer
    {
        std::string activeShaderProgramName;

    public:
        Camera camera;

        virtual ~Canvas();

        void useShaderProgram(const std::string& name);

        void clear(Color color);
        virtual void bind() const;
        //void draw(const randar::Drawable& drawable) const;
    };
}

#endif

#ifndef RANDAR_RENDER_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_RENDER_TEXTURE_HPP

#include <randar/render/Canvas.hpp>

namespace randar
{
    class RenderTexture : virtual public Canvas
    {
        GLuint framebuffer;
        GLuint texture;
        GLuint renderBuffer;

    public:
        RenderTexture();
        ~RenderTexture();

        virtual void bind() const override;
    };
}

#endif

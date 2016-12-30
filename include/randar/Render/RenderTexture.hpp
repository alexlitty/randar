#ifndef RANDAR_RENDER_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_RENDER_TEXTURE_HPP

#include <stdexcept>
#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct RenderTexture : virtual public GpuResource
    {
        GLuint framebuffer;
        GLuint texture;

    public:
        RenderTexture();
        ~RenderTexture();

        virtual void bind() const;
    };
}

#endif

#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/engine/GpuResource.hpp>

namespace randar
{
    struct Texture : virtual public GpuResource
    {
        enum Type
        {
            DEPTH
        };

        const Texture::Type type;
        const unsigned int width;
        const unsigned int height;

        Texture(
            ::GLuint initGlName,
            Texture::Type initType,
            unsigned int initWidth,
            unsigned int initHeight
        );
    };
}

#endif

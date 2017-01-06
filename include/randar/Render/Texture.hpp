#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Texture : virtual public GpuResource
    {
        enum Type
        {
            RGBA,
            DEPTH
        };

        const Texture::Type textureType;
        unsigned int width;
        unsigned int height;

        Texture(
            Texture::Type initTextureType,
            unsigned int initWidth,
            unsigned int initHeight,
            const std::string& initName = "");

        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif

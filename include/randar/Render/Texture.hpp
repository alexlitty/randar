#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Texture : virtual public GpuResource
    {
        enum Type
        {
            INVALID,
            RGBA,
            DEPTH
        };

        const Texture::Type type;
        unsigned int width;
        unsigned int height;

        Texture(
            Texture::Type initType = Texture::Type::INVALID,
            unsigned int initWidth = 1,
            unsigned int initHeight = 1,
            const std::string& initName = "");

        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif

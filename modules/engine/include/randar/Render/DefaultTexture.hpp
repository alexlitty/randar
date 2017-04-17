#ifndef RANDAR_RENDER_DEFAULT_TEXTURE_HPP
#define RANDAR_RENDER_DEFAULT_TEXTURE_HPP

#include <randar/Render/Texture.hpp>

namespace randar
{
    /**
     * Retrieves an empty, default texture generated on-the-fly.
     */
    Texture& getDefaultTexture(
        Gpu& gpu,
        const std::string& type,
        uint32_t width,
        uint32_t height);
}

#endif

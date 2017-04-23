#ifndef RANDAR_RENDER_DEFAULT_TEXTURE_HPP
#define RANDAR_RENDER_DEFAULT_TEXTURE_HPP

#include <randar/Render/Texture.hpp>

namespace randar
{
    /**
     * Retrieves an empty, default texture generated on-the-fly.
     */
    Texture& getDefaultTexture(
        GraphicsContext& ctx,
        uint32_t width,
        uint32_t height,
        const std::string& type);
}

#endif

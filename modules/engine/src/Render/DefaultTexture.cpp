#include <randar/Render/DefaultTexture.hpp>

randar::Texture& randar::getDefaultTexture(
    GraphicsContext& ctx,
    uint32_t width,
    uint32_t height,
    const std::string& type)
{
    static std::map<
        std::string,
        std::map<std::pair<uint32_t, uint32_t>, Texture*>
    > defaultTextures;

    auto dimensions = std::make_pair(width, height);
    if (defaultTextures[type][dimensions] == nullptr) {
        Texture *texture = new Texture(ctx, width, height, type);
        defaultTextures[type][dimensions] = texture;
    }

    return *defaultTextures[type][dimensions];
}

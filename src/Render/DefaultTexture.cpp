#include <randar/Render/DefaultTexture.hpp>

randar::Texture& randar::getDefaultTexture(
    const std::string& type,
    uint32_t width,
    uint32_t height)
{
    static std::map<
        std::string,
        std::map<std::pair<uint32_t, uint32_t>, Texture*>
    > defaultTextures;

    auto dimensions = std::make_pair(width, height);
    if (defaultTextures[type][dimensions] == nullptr) {
        defaultTextures[type][dimensions] = new Texture(type, width, height);
    }

    return *defaultTextures[type][dimensions];
}

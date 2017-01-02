#include <randar/Render/Texture.hpp>

const randar::Resource::Type randar::Texture::type = randar::Resource::TEXTURE;
randar::Resource::Type randar::Texture::getType() const
{
    return this->type;
}

randar::Texture::Texture(
    randar::Texture::Type initTextureType,
    unsigned int initWidth,
    unsigned int initHeight,
    const std::string& initName
) :
  randar::Resource(initName),
  textureType(initTextureType),
  width(initWidth),
  height(initHeight)
{

}

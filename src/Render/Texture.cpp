#include <randar/Render/Texture.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Texture::Texture(
    randar::Texture::Type initType,
    unsigned int initWidth,
    unsigned int initHeight,
    const std::string& initName
) :
  randar::Resource(initName),
  type(initType),
  width(initWidth),
  height(initHeight)
{

}

// Resizes this texture.
void randar::Texture::resize(unsigned int width, unsigned int height)
{

}

void randar::Texture::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

void randar::Texture::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}

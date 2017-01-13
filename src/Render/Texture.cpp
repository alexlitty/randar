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
    this->gpu.resize(*this, width, height);
}

// Initializes this texture.
void randar::Texture::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

// Destroys this texture.
void randar::Texture::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}

// Converts this texture to a JSON representation.
Json randar::Texture::toJson() const
{
    Json result;
    result["test"] = 4;
    return result;
}

#include <randar/Render/Texture.hpp>
#include <randar/Engine/Gpu.hpp>
#include <randar/Data/BinaryFileInput.hpp>

// New texture constructor.
randar::Texture::Texture(
    std::string initType,
    unsigned int initWidth,
    unsigned int initHeight
) :
  type(initType),
  width(initWidth),
  height(initHeight)
{
    this->gpu.initialize(*this);
}

// Construct from a file.
randar::Texture::Texture(const std::string& file)
: randar::FileResource(file)
{
    BinaryFileInput stream(file);
}

// Destructor.
randar::Texture::~Texture()
{
    this->gpu.destroy(*this);
}

// Saves this texture to its file.
bool randar::Texture::save()
{

}

// Checks the validity of this texture.
bool randar::Texture::isValid(std::string& error) const
{
    if (!this->isRgba() && !this->isDepth()) {
        error = "Invalid type: " + this->type;
    }

    else if (width == 0 || height == 0 || width > 1024 || height > 1024) {
        error = "Invalid dimensions: "
              + std::to_string(this->width)
              + "x"
              + std::to_string(this->height);
    }

    else {
        return true;
    }
    return false;
}

// Checks which kind of texture this is.
bool randar::Texture::isRgba() const
{
    return this->type == "rgba";
}

bool randar::Texture::isDepth() const
{
    return this->type == "depth";
}

// Resizes this texture.
void randar::Texture::resize(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    this->gpu.resize(*this);
}

// Retrieves the width and height of this texture.
unsigned int randar::Texture::getWidth() const
{
    return this->width;
}

unsigned int randar::Texture::getHeight() const
{
    return this->height;
}

// Converts this texture to a JSON representation.
Json randar::Texture::toJson() const
{
    return {
        { "type",   this->type   },
        { "width",  this->width  },
        { "height", this->height }
    };
}

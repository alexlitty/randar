#include <randar/Log/DefaultLog.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Engine/Gpu.hpp>

// New texture constructor.
randar::Texture::Texture(
    std::string initType,
    uint32_t initWidth,
    uint32_t initHeight
) :
  type(initType),
  width(initWidth),
  height(initHeight)
{
    if (this->width == 0 || this->height == 0 || this->width > 4096 || this->height > 4096) {
        throw std::runtime_error(
            "Invalid texture dimensions ("
            + std::to_string(this->width) + "x"
            + std::to_string(this->height) + ")"
        );
    }

    this->gpu.initialize(*this);
}

// Construct from a file.
randar::Texture::Texture(const std::string& file)
{

}

// Destructor.
randar::Texture::~Texture()
{
    this->gpu.destroy(*this);
}

// Saves this texture to its file.
bool randar::Texture::save()
{
    return true;
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
std::string randar::Texture::getType() const
{
    return this->type;
}

bool randar::Texture::isRgba() const
{
    return this->type == "rgba";
}

bool randar::Texture::isDepth() const
{
    return this->type == "depth";
}

// Clears this texture with a color.
void randar::Texture::clear(const Color& color)
{
    std::vector<uint8_t> values;

    uint32_t pixelCount = this->width * this->height;
    for (unsigned int i = 0; i < pixelCount; i++) {
        values.push_back(color.r);
        values.push_back(color.g);
        values.push_back(color.b);
        values.push_back(color.a);
    }

    this->gpu.write(*this, values.data(), GL_RGBA);
}

// Resizes this texture.
void randar::Texture::resize(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    this->gpu.resize(*this);
}

// Writes texture data to the GPU.
void randar::Texture::write()
{
    this->write(this->data.data(), GL_RGBA);
}

void randar::Texture::write(const GLvoid* data, GLenum format)
{
    this->write(
        Rect<uint32_t>(0, 0, this->getWidth(), this->getHeight()),
        data,
        format
    );
}

void randar::Texture::write(
    const randar::Rect<uint32_t>& rect,
    const GLvoid* data,
    GLenum format)
{
    this->gpu.write(*this, rect, data, format);
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
        { "name",   "Untitled Texture" },

        { "type",   this->type   },
        { "width",  this->width  },
        { "height", this->height }
    };
}

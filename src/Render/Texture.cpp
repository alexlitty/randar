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
//: randar::FileResource(file)
{
    /*this->setFile(file);
    BinaryFileReader stream(this->file);

    stream.read(this->type);
    stream.read(this->width);
    stream.read(this->height);

    // Invalid dimensions.
    if (this->width == 0 || this->height == 0 || this->width > 4096 || this->height > 4096) {
        throw std::runtime_error("Invalid texture dimensions");
    }

    unsigned int requiredSize = this->width * this->height * 4;
    try {
        uint8_t value;

        for (unsigned int i = 0; i < requiredSize; i++) {
            stream.read(value);
            this->data.push_back(value);
        }
    }

    // Fill missing data with opaque white.
    catch (std::runtime_error error) {
        for (unsigned int i = data.size(); i < requiredSize; i++) {
            this->data.push_back(255);
        }

        randar::logError("Texture data missing while importing");
    }

    this->gpu.initialize(*this);*/
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
    /*BinaryFileWriter stream(this->file);

    stream.write(this->type);
    stream.write(this->width);
    stream.write(this->height);

    for (auto value : this->data) {
        stream.write(value);
    }

    // Fill missing data with opaque white.
    unsigned int requiredSize = this->width * this->height * 4;
    if (this->data.size() < requiredSize) {
        for (unsigned int i = data.size(); i < requiredSize; i++) {
            stream.write(255);
        }

        randar::logError("Texture data missing while saving");
    }

    return true;*/
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

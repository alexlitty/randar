#include <randar/Render/Texture.hpp>
#include <randar/System/GraphicsContext.hpp>

// New texture constructor.
randar::Texture::Texture(
    randar::GraphicsContext& context,
    uint32_t initWidth,
    uint32_t initHeight,
    std::string initType,
) :
  randar::GpuResource(context),
  type(initType),
  width(initWidth),
  height(initHeight)
{
    if (!this->hasDimensions() || this->getWidth() > 4096 || this->getHeight() > 4096) {
        throw std::runtime_error("Invalid texture dimensions");
    }

    // Create.
    ::glGenTextures(1, &this->glName);
    this->bind();

    // Configure.
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Clear the texture, implicitly sending the desired texture size.
    this->clear();
}

// Construct from a file.
randar::Texture::Texture(const std::string& file)
{

}

// Destructor.
randar::Texture::~Texture()
{
    if (this->gpu) {
        this->gpu->destroy(*this);
    }
}

// Binds the texture for further operations.
void randar::Texture::bind()
{
    ::glBindTexture(GL_TEXTURE_2D, this->glName);
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
        values.push_back(color.r());
        values.push_back(color.g());
        values.push_back(color.b());
        values.push_back(color.a());
    }

    if (this->gpu) {
        this->gpu->write(*this, values.data(), GL_RGBA);
    }
}

// Resizes this texture.
void randar::Texture::resize(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    if (this->gpu) {
        this->gpu->resize(*this);
    }
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
    if (this->gpu) {
        this->gpu->write(*this, rect, data, format);
    }
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

// Patches this resource.
void randar::Texture::patch(Json json)
{
    for (auto it = json.begin(); it != json.end(); it++) {
        std::string key = it.key();

        if (key == "name") {
            this->name = it.value();
        }
    }
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

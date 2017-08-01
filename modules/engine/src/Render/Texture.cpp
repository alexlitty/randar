#include <randar/Render/Texture.hpp>

// New texture constructor.
randar::Texture::Texture(
    randar::GraphicsContext& context,
    uint32_t initWidth,
    uint32_t initHeight,
    const std::string& initType
)
: randar::GraphicsContextResource(&context),
  randar::Dimensional2<uint32_t>(initWidth, initHeight),
  type(initType)
{
    this->initialize();
}

// Destructor.
randar::Texture::~Texture()
{
    if (this->isInitialized()) {
        this->uninitialize();
    }
}

// Initializes the texture on the associated graphics context.
void randar::Texture::initialize()
{
    if (this->isInitialized()) {
        throw std::runtime_error("Texture is already initialized");
    }

    if (!this->ctx) {
        throw std::runtime_error("Texture is not associated with a context");
    }

    if (this->type != "rgba" && this->type != "depth") {
        throw std::runtime_error("Invalid texture type");
    }

    this->ctx->use();
    ::glGenTextures(1, &this->glName);

    this->ctx->check("Cannot generate texture");
    if (!this->isInitialized()) {
        throw std::runtime_error("Failed to generate texture");
    }

    this->bind();
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    this->reset();
}

// Uninitializes the texture from the associated graphics context.
void randar::Texture::uninitialize()
{
    if (!this->isInitialized()) {
        throw std::runtime_error("Texture is not initialized");
    }

    this->ctx->use();
    ::glDeleteTextures(1, &this->glName);
}

// Checks if the texture is initialized.
bool randar::Texture::isInitialized() const
{
    return this->ctx && this->glName != 0;
}

// Binds the texture for further operations.
void randar::Texture::bind()
{
    if (this->glName == 0) {
        throw std::runtime_error("Cannot bind uninitialized texture");
    }

    this->ctx->use();
    ::glBindTexture(GL_TEXTURE_2D, this->glName);
    this->ctx->check("Cannot bind texture");
}

// Sets the texture as active for further operations.
void randar::Texture::active(uint16_t index)
{
    ::glActiveTexture(GL_TEXTURE0 + index);
    this->bind();
}

// Resets the texture with arbitrary data.
void randar::Texture::reset()
{
    this->bind();

    if (this->type == "rgba") {
        ::glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            this->getWidth(),
            this->getHeight(),
            0,
            GL_RGBA,
            GL_FLOAT,
            nullptr
        );
    }

    else if (this->type == "depth") {
        ::glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_DEPTH_COMPONENT16,
            this->getWidth(),
            this->getHeight(),
            0,
            GL_DEPTH_COMPONENT,
            GL_FLOAT,
            nullptr
        );
    }

    else {
        throw std::runtime_error("Resetting invalid texture type");
    }

    this->ctx->check("Cannot reset texture");
}

// Resizes this texture.
void randar::Texture::resize(uint32_t newWidth, uint32_t newHeight)
{
    Dimensional2<uint32_t>::resize(newWidth, newHeight);
    this->reset();
}

// Reads the contents of the texture.
randar::Image randar::Texture::image()
{
    Image result;
    this->bind();

    result.resize(this->getWidth(), this->getHeight());
    result.layout(Image::LAYOUT::FLIP_VERTICAL);

    if (this->type == "rgba") {
        ::glGetTexImage(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            GL_FLOAT,
            result.raw()
        );
    }

    else if (this->type == "depth") {
        float* data = new float[this->getWidth() * this->getHeight()];

        ::glGetTexImage(
            GL_TEXTURE_2D,
            0,
            GL_DEPTH_COMPONENT,
            GL_FLOAT,
            data
        );

        for (uint32_t x = 0; x < this->getWidth(); x++) {
            for (uint32_t y = 0; y < this->getHeight(); y++) {
                float value = data[(y * this->getWidth()) + x];
                result.setPixel(x, y, value, value, value);
            }
        }

        delete[] data;
    }

    else {
        throw std::runtime_error("Reading invalid texture type");
    }

    this->ctx->check("Cannot read texture");
    return result;
}

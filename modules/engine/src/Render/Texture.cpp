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
            GL_DEPTH_COMPONENT,
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
void randar::Texture::read(randar::Image& image)
{
    this->bind();

    image.resize(this->getWidth(), this->getHeight());
    image.layout(Image::LAYOUT::FLIP_VERTICAL);

    if (this->type == "rgba") {
        ::glGetTexImage(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            GL_FLOAT,
            image.raw()
        );
    }

    else {
        throw std::runtime_error("Reading invalid texture type");
    }

    this->ctx->check("Cannot read texture");
}

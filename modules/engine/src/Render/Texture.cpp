#include <randar/Render/Texture.hpp>
#include <randar/System/GraphicsContext.hpp>

// New texture constructor.
randar::Texture::Texture(
    randar::GraphicsContext& context,
    uint32_t initWidth,
    uint32_t initHeight,
    const std::string& initType
) :
  randar::GpuResource(context),
  randar::Dimensional2(
    initWidth,
    initHeight,
    RANDAR_TEXTURE_MAX_WIDTH,
    RANDAR_TEXTURE_MAX_HEIGHT),
  type(initType)
{
    if (type != "rgba" && type != "depth") {
        throw std::runtime_error("Invalid texture type");
    }

    // Create.
    ::glGenTextures(1, &this->glName);
    this->bind();

    // Configure.
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ::glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    this->reset();
}

// Destructor.
randar::Texture::~Texture()
{
    this->ctx->use();
    ::glDeleteFramebuffers(1, &this->glName);
}

// Binds the texture for further operations.
void randar::Texture::bind()
{
    this->ctx->use();
    ::glBindTexture(GL_TEXTURE_2D, this->glName);
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
}

// Resizes this texture.
void randar::Texture::resize(uint32_t width, uint32_t height)
{
    randar::Dimensional2::resize(width, height)
    this->reset();
}

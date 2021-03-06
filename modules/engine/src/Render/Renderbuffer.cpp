#include <randar/Render/Renderbuffer.hpp>

// Constructors.
randar::Renderbuffer::Renderbuffer(
    uint32_t initWidth,
    uint32_t initHeight,
    const std::string& initBufferType)
: randar::Renderbuffer(randar::context(), initWidth, initHeight, initBufferType)
{

}

randar::Renderbuffer::Renderbuffer(
    randar::GraphicsContext& context,
    uint32_t initWidth,
    uint32_t initHeight,
    const std::string& initBufferType)
: randar::GraphicsContextResource(&context),
  bufferType(initBufferType)
{
    this->bindContext();

    ::glGenRenderbuffers(1, &this->glName);
    this->ctx->check("Cannot generate renderbuffer");
    if (this->glName == 0) {
        throw std::runtime_error("Failed to create renderbuffer");
    }

    this->resize(initWidth, initHeight);
}

// Destructor.
randar::Renderbuffer::~Renderbuffer()
{
    if (this->ctx) {
        this->ctx->use();

        if (this->glName > 0) {
            ::glDeleteRenderbuffers(1, &this->glName);
        }
    }
}

// Binds the renderbuffer for further operations.
void randar::Renderbuffer::bind()
{
    if (this->glName == 0) {
        throw std::runtime_error("Cannot bind uninitialized renderbuffer");
    }

    this->bindContext();
    ::glBindRenderbuffer(GL_RENDERBUFFER, this->glName);
    this->ctx->check("Cannot bind renderbuffer");
}

// Resizes this renderbuffer.
void randar::Renderbuffer::resize(uint32_t newWidth, uint32_t newHeight)
{
    Dimensional2<uint32_t>::resize(newWidth, newHeight);

    this->bind();
    ::glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT,
        this->getWidth(),
        this->getHeight()
    );

    this->ctx->check("Cannot resize renderbuffer");
}

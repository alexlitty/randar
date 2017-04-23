#include <randar/Render/Renderbuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Renderbuffer::Renderbuffer(
    randar::GraphicsContext& context,
    uint32_t initWidth,
    uint32_t initHeight,
    const std::string& initBufferType)
: randar::GpuResource(context),
  bufferType(initBufferType)
{
    this->ctx->use();
    ::glGenRenderbuffers(1, &this->glName);

    this->ctx->check();
    if (this->glName == 0) {
        throw std::runtime_error("Failed to create renderbuffer");
    }

    this->resize(initWidth, initHeight);
}

// Destructor.
randar::Renderbuffer::~Renderbuffer()
{
    this->ctx->use();
    if (this->glName > 0) {
        ::glDeleteRenderbuffers(1, &this->glName);
    }
}

// Binds the renderbuffer for further operations.
void randar::Renderbuffer::bind()
{
    this->ctx->use();
    ::glBindRenderbuffer(GL_RENDERBUFFER, this->glName);
}

// Resizes this renderbuffer.
void randar::Renderbuffer::resize(uint32_t newWidth, uint32_t newHeight)
{
    randar::Dimensional2<uint32_t>::resize(newWidth, newHeight);

    this->bind();
    ::glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT,
        this->getWidth(),
        this->getHeight()
    );

    this->ctx->check();
}

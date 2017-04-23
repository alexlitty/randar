#include <randar/Render/Renderbuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Renderbuffer::Renderbuffer(
    randar::GraphicsContext& context,
    uint32_t initWidth,
    uint32_t initHeight,
    const std::string& initType)
: randar::GpuResource(context),
  randar::Dimensional2<uint32_t>(initWidth, initHeight),
  bufferType(initBufferType)
{
    ::glGenRenderbuffers(1, &this->glName);

    this->ctx->check();
    if (this->glName == 0) {
        throw std::runtime_error("Failed to create renderbuffer");
    }
}

// Constructs a new renderbuffer from an existing one.
randar::Renderbuffer::Renderbuffer(const randar::Renderbuffer& other)
: type(other.type),
  width(other.width),
  height(other.height)
{
    if (this->gpu) {
        this->gpu->initialize(*this);
    }
}

// Destructor.
randar::Renderbuffer::~Renderbuffer()
{
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
    // @@@
}

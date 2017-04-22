#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a default framebuffer.
randar::Framebuffer::Framebuffer(randar::Window& window)
: randar::GpuResource(window.context()),
  randar::Dimensional2<uint32_t>(window),
  isDefaultFramebuffer(true),
  texture(nullptr),
  depthBuffer(nullptr)
{

}

// Constructs a new framebuffer.
/*randar::Framebuffer::Framebuffer(
    randar::GraphicsContext& context,
    std::string textureType,
    bool enableDepthBuffer,
    uint32_t initWidth,
    uint32_t initHeight)
: randar::GpuResource(context),
  randar::Dimensional2<uint32_t>(initWidth, initHeight),
  isDefaultFramebuffer(false),
  texture(nullptr),
  depthBuffer(nullptr)
{
    ::glGenFramebuffers(1, framebuffer);
    this->bind(); // @@@

    if (this->texture) {
        // initialize(texture)
        // bind(texture)
        // if (rgba) {
            // glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
            // glEnum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
            // glDrawBuffers(1, drawBuffers);
        // }

        // if (depth) {
            // glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
        // }
    }

    if (this->depthBuffer) {
        // initialize(depthBuffer)
        // bind(depthBuffer)
    }

    if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Error while initializing framebuffer");
    }
}*/

// Destructor.
randar::Framebuffer::~Framebuffer()
{
    ::glDeleteFramebuffers(1, this->glName);
    if (this->texture) {
        // delete this->texture;
    }

    if (this->depthBuffer) {
        // delete this->depthBuffer;
    }
}

// Binds the framebuffer for further operations.
void randar::Framebuffer::bind()
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, this->glName);

    const Viewport &viewport = this->camera.viewport;
    ::glViewport(viewport.x1, viewport.y1, viewport.x2, viewport.y2);
}

// Clears the framebuffer with an optional color.
void randar::Framebuffer::clear(const randar::Color& color)
{
    this->gpu->clear(*this, color);
}

// Resizes this framebuffer and its dependencies.
void randar::Framebuffer::resize(randar::Dimensional2<uint32_t> dimensions)
{
    this->resize(dimensions.getWidth(), dimensions.getHeight());
}

void randar::Framebuffer::resize(uint32_t newWidth, uint32_t newHeight)
{
    if (!this->isDefault()) {
        this->width = newWidth;
        this->height = newHeight;
        this->gpu->resize(*this);
    }
}

// Gets the width of this framebuffer.
uint32_t randar::Framebuffer::getWidth() const
{
    return this->width;
}

// Gets the height of this framebuffer.
uint32_t randar::Framebuffer::getHeight() const
{
    return this->height;
}

// Checks whether this framebuffer has a texture.
bool randar::Framebuffer::hasTexture() const
{
    return this->texture != nullptr;
}

// Checks whether this framebuffer has a depth buffer.
bool randar::Framebuffer::hasDepthBuffer() const
{
    return this->depthBuffer != nullptr;
}

// Gets the texture.
randar::Texture& randar::Framebuffer::getTexture()
{
    return *this->texture;
}

// Gets the depth buffer.
randar::Renderbuffer& randar::Framebuffer::getDepthBuffer()
{
    return *this->depthBuffer;
}

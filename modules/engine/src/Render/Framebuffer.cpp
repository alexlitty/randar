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

// Constructs and initializes a new framebuffer.
randar::Framebuffer::Framebuffer(
    randar::Gpu& gpuInit,
    std::string textureType,
    bool enableDepthBuffer,
    uint32_t initWidth,
    uint32_t initHeight)
: randar::GpuResource(&gpuInit),
  randar::Dimensional2<uint32_t>(initWidth, initHeight),
  isDefaultFramebuffer(false),
  texture(new randar::Texture(this->gpu, textureType, initWidth, initHeight)),
  depthBuffer(new randar::Renderbuffer(this->gpu, randar::Renderbuffer::DEPTH, initWidth, initHeight))
{
    this->gpu->initialize(*this);
}

// Destructor.
randar::Framebuffer::~Framebuffer()
{
    if (this->isInitialized()) {
        this->gpu->destroy(*this);
    }

    if (this->hasTexture()) {
        this->gpu->destroy(*this->texture);
        delete this->texture;
    }

    if (this->hasDepthBuffer()) {
        this->gpu->destroy(*this->depthBuffer);
        delete this->depthBuffer;
    }
}

// Whether this is the default framebuffer.
bool randar::Framebuffer::isDefault() const
{
    return this->isDefaultFramebuffer;
}

// Whether this framebuffer is initialized on the GPU.
bool randar::Framebuffer::isInitialized() const
{
    return this->isDefault() || randar::GpuResource::isInitialized();
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

#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a default framebuffer.
randar::Framebuffer::Framebuffer()
: isDefaultFramebuffer(true),
  texture(nullptr),
  depthBuffer(nullptr)
{
    int width, height;
    ::glfwGetFramebufferSize(&this->gpu.getWindow(), &width, &height);

    if (width <= 0 || height <= 0) {
        throw std::runtime_error(
            "Invalid default framebuffer dimensions ("
            + std::to_string(width) + "x"
            + std::to_string(height) + ")"
        );
    }

    this->resize(width, height);
}

// Constructs and initializes a new framebuffer.
randar::Framebuffer::Framebuffer(
    std::string textureType,
    bool enableDepthBuffer,
    uint32_t initWidth,
    uint32_t initHeight)
: isDefaultFramebuffer(false),
  texture(new randar::Texture(textureType, initWidth, initHeight)),
  depthBuffer(new randar::Renderbuffer(randar::Renderbuffer::DEPTH, initWidth, initHeight)),
  width(initWidth),
  height(initHeight)
{
    this->gpu.initialize(*this);
}

// Destructor.
randar::Framebuffer::~Framebuffer()
{
    if (this->isInitialized()) {
        this->gpu.destroy(*this);
    }

    if (this->hasTexture()) {
        this->gpu.destroy(*this->texture);
        delete this->texture;
    }

    if (this->hasDepthBuffer()) {
        this->gpu.destroy(*this->depthBuffer);
        delete this->depthBuffer;
    }
}

// Retrieves the default framebuffer.
randar::Framebuffer& randar::Framebuffer::getDefault()
{
    static Framebuffer defaultFramebuffer;
    return defaultFramebuffer;
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
    this->gpu.clear(*this, color);
}

// Resizes this framebuffer and its dependencies.
void randar::Framebuffer::resize(uint32_t newWidth, uint32_t newHeight)
{
    this->width = newWidth;
    this->height = newHeight;
    this->gpu.resize(*this);
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

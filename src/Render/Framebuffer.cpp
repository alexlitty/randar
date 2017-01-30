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

    this->camera.viewport = Viewport(0, 0, width, height);
}

// Constructs and initializes a new framebuffer.
randar::Framebuffer::Framebuffer(
    std::string textureType,
    bool enableDepthBuffer,
    unsigned int width,
    unsigned int height)
: isDefaultFramebuffer(false),
  texture(new randar::Texture(textureType, width, height)),
  depthBuffer(new randar::Renderbuffer(randar::Renderbuffer::DEPTH, width, height))
{
    this->camera.viewport = Viewport(0, 0, width, height);
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
void randar::Framebuffer::resize(unsigned int width, unsigned int height)
{
    this->gpu.resize(*this, width, height);
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

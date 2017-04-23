#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs an off-screen framebuffer.
randar::Framebuffer::Framebuffer(randar::GraphicsContext& context)
: randar::GpuResource(context),
  isDefaultFramebuffer(false),
  texture(nullptr),
  depthBuffer(nullptr),
  window(nullptr)
{
    this->reset();
}

// Constructs a default framebuffer.
randar::Framebuffer::Framebuffer(randar::Window& initWindow)
: randar::GpuResource(initWindow.context()),
  randar::Dimensional2<uint32_t>(initWindow),
  isDefaultFramebuffer(true),
  texture(nullptr),
  depthBuffer(nullptr),
  window(&initWindow)
{

}

// Destructor.
randar::Framebuffer::~Framebuffer()
{
    if (!this->isDefaultFramebuffer) {
        ::glDeleteFramebuffers(1, &this->glName);
    }

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
    if (this->window) {
        this->window->use();
    } else {
        this->ctx->use();
    }
    ::glBindFramebuffer(GL_FRAMEBUFFER, this->glName);

    const Viewport &viewport = this->camera.viewport;
    ::glViewport(viewport.x1, viewport.y1, viewport.x2, viewport.y2);
}

// Checks the sanity of framebuffer attachments.
bool randar::Framebuffer::check()
{
    if (this->isDefaultFramebuffer) {
        return true;
    }
    return ::glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

// Resets all attachments.
void randar::Framebuffer::reset()
{
    if (this->isDefaultFramebuffer) {
        throw std::runtime_error("Cannot modify default framebuffer attachments");
    }

    this->bind();
    if (this->glName > 0) {
        ::glDeleteFramebuffers(1, &this->glName);
    }
    ::glGenFramebuffers(1, &this->glName);
}

// Attachs a texture to the framebuffer.
void randar::Framebuffer::attach(randar::Texture& texture)
{
    this->reset();
    this->resize(texture);
    this->texture = &texture;

    if (texture.type == "rgba") {
        ::glFramebufferTexture(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            texture,
            0
        );

        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        ::glDrawBuffers(1, drawBuffers);

        // initialize(depthBuffer)
        // bind(depthBuffer)
    }

    /*else if (texture.type == "depth") {
        ::glFramebufferTexture(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            texture,
            0
        );
    }*/

    else {
        throw std::runtime_error("Attaching texture with invalid type");
    }

    if (!this->check()) {
        throw std::runtime_error("Bad framebuffer attachments");
    }
}

// Clears the framebuffer with an optional color.
void randar::Framebuffer::clear(const randar::Color& color)
{
    this->bind();
    ::glClearColor(color.r(), color.g(), color.b(), color.a());
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Resizes this framebuffer and its dependencies.
void randar::Framebuffer::resize(randar::Dimensional2<uint32_t> dimensions)
{
    this->resize(dimensions.getWidth(), dimensions.getHeight());
}

void randar::Framebuffer::resize(uint32_t newWidth, uint32_t newHeight)
{
    randar::Dimensional2<uint32_t>::resize(newWidth, newHeight);
    this->camera.viewport = Viewport(0, 0, newWidth, newHeight);
    if (this->isDefaultFramebuffer) {
        throw std::runtime_error("Resizing default framebuffer not supported yet");
    }

    if (this->texture) {
        this->texture->resize(newWidth, newHeight);
    }

    if (this->depthBuffer) {
        // this->depthBuffer->resize(newWidth, newHeight);
    }
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

// Reads the contents of the framebuffer.
void randar::Framebuffer::read(randar::Image& image)
{
    this->bind();

    image.resize(this->getWidth(), this->getHeight());
    image.layout(Image::LAYOUT::FLIP_VERTICAL);

    ::glReadPixels(
        0,
        0,
        image.getWidth(),
        image.getHeight(),
        GL_RGBA,
        GL_FLOAT,
        image.raw()
    );
}

randar::Image randar::Framebuffer::read()
{
    Image image;
    this->read(image);
    return image;
}

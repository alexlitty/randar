#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs an off-screen framebuffer.
randar::Framebuffer::Framebuffer(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  isDefaultFramebuffer(false),
  texture(nullptr),
  depthBuffer(nullptr),
  window(nullptr)
{
    this->reset();
}

// Constructs a default framebuffer.
randar::Framebuffer::Framebuffer(randar::Window& initWindow)
: randar::GraphicsContextResource(&initWindow.context()),
  randar::Dimensional2<uint32_t>(initWindow.getWidth(), initWindow.getHeight()),
  isDefaultFramebuffer(true),
  texture(nullptr),
  depthBuffer(nullptr),
  window(&initWindow)
{

}

// Destructor.
randar::Framebuffer::~Framebuffer()
{
    this->destroy();
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
    this->ctx->check("Cannot bind framebuffer");

    if (this->hasDimensions()) {
        const Viewport &viewport = this->camera.viewport;
        ::glViewport(viewport.x1, viewport.y1, viewport.x2, viewport.y2);
    }
}

// Checks the sanity of framebuffer attachments.
void randar::Framebuffer::check()
{
    static std::map<GLenum, std::string> errorDescriptions = {
        { GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, "Attachment incomplete" },
        { GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, "No images attached" },
        { GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, "Invalid draw buffer" },
        { GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, "Invalid read buffer" },
        { GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, "Inconsistent sampling configurations" },
        { GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS, "Inconsistent layering" },
        { GL_FRAMEBUFFER_UNDEFINED, "Nonexistent default framebuffer" },
        { GL_FRAMEBUFFER_UNSUPPORTED, "Configuration not supported" }
    };

    this->ctx->check("Uncaught GL error before Framebuffer sanity check");

    if (this->isDefaultFramebuffer) {
        if (!this->window) {
            throw std::runtime_error("Default framebuffer is missing window");
        }
        return;
    }

    this->bind();
    this->status = ::glCheckFramebufferStatus(GL_FRAMEBUFFER);
    this->ctx->check("Cannot check framebuffer status");
    if (this->status == GL_FRAMEBUFFER_COMPLETE) {
        return;
    }

    std::string description = errorDescriptions[status];
    if (description.empty()) {
        description = "Unknown GL status #" + std::to_string(status);
    }

    throw std::runtime_error("Framebuffer incomplete: " + description);
}

// Destroys this framebuffer and removes its attachments.
void randar::Framebuffer::destroy()
{
    if (this->glName > 0) {
        this->ctx->use();
        ::glDeleteFramebuffers(1, &this->glName);
        this->ctx->check("Cannot destroy framebuffer");
        this->glName = 0;
    }

    if (this->texture) {
        this->texture = nullptr;
    }

    if (this->depthBuffer) {
        delete this->depthBuffer;
        this->depthBuffer = nullptr;
    }
}

// Resets all attachments.
void randar::Framebuffer::reset()
{
    if (this->isDefaultFramebuffer) {
        throw std::runtime_error("Cannot modify default framebuffer attachments");
    }

    this->destroy();

    this->ctx->use();
    ::glGenFramebuffers(1, &this->glName);
    this->ctx->check("Cannot generate framebuffer");
    if (this->glName == 0) {
        throw std::runtime_error("Failed to reset framebuffer");
    }

    this->resize(0, 0);
}

// Attachs a texture to the framebuffer.
void randar::Framebuffer::attach(randar::Texture& texture)
{
    if (this->window) {
        throw std::runtime_error("Cannot add attachments to window framebuffer");
    }

    if (this->texture) {
        throw std::runtime_error("Framebuffer already has an attached texture");
    }

    if (this->depthBuffer) {
        throw std::runtime_error("Framebuffer already has an attached depth buffer");
    }

    if (!texture.hasDimensions()) {
        throw std::runtime_error("Attachment must have positive dimensions");
    }

    this->resize(texture.getWidth(), texture.getHeight());
    this->texture = &texture;

    this->bind();
    this->texture->bind();

    if (texture.type == "rgba") {
        ::glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            texture.getGlName(),
            0);
        this->ctx->check("Cannot attach texture");

        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        ::glDrawBuffers(1, drawBuffers);
        this->ctx->check("Cannot set draw buffers");

        this->depthBuffer = new Renderbuffer(
            *this->ctx,
            this->getWidth(),
            this->getHeight(),
            "depth"
        );

        ::glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER,
            this->depthBuffer->getGlName()
        );
        this->ctx->check("Cannot attach renderbuffer");
    }

    else {
        throw std::runtime_error("Attaching texture with invalid type");
    }

    this->check();
}

// Clears the framebuffer with an optional color.
void randar::Framebuffer::clear(const randar::Color& color)
{
    this->bind();
    ::glClearColor(color.r(), color.g(), color.b(), color.a());
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Resizes this framebuffer and its dependencies.
void randar::Framebuffer::resize(uint32_t newWidth, uint32_t newHeight)
{
    if (this->isDefaultFramebuffer) {
        throw std::runtime_error("Resizing default framebuffer not supported yet");
    }

    Dimensional2<uint32_t>::resize(newWidth, newHeight);
    this->camera.viewport = Viewport(0, 0, newWidth, newHeight);

    if (this->texture) {
        this->texture->resize(newWidth, newHeight);
    }

    if (this->depthBuffer) {
        this->depthBuffer->resize(newWidth, newHeight);
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

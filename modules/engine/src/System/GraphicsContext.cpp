#include <map>
#include <randar/System/GraphicsContextResource.hpp>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/System/Window.hpp>

// Allows us to pass attributes while creating a context.
typedef GLXContext (*glXCreateContextAttribsARBProc)(
    Display*,
    GLXFBConfig,
    GLXContext,
    Bool,
    const int*
);

// Constructor.
randar::GraphicsContext::GraphicsContext()
{
    // Load extensions.
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
        (glXCreateContextAttribsARBProc)glXGetProcAddressARB(
            (const GLubyte *) "glXCreateContextAttribsARB"
        );

    if (!glXCreateContextAttribsARB) {
        throw std::runtime_error("No support for GLX_ARB_create_context");
    }

    int fbAttribs[] = {
        GLX_X_RENDERABLE, true,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,

        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DOUBLEBUFFER, true,

        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        None
    };

    int pbAttribs[] = {
        GLX_PBUFFER_WIDTH, 1,
        GLX_PBUFFER_HEIGHT, 1,
        None
    };

    int ctxAttribs[] = {
        //GLX_CONTEXT_MAJOR_VERSION, 3,
        //GLX_CONTEXT_MINOR_VERSION, 3,
        None
    };

    // Get a local X display.
    this->display = ::XOpenDisplay(0);

    // Find a proper framebuffer configuration.
    int fbCount = 0;
    this->fbConfigs = ::glXChooseFBConfig(
        this->display,
        DefaultScreen(this->display),
        fbAttribs,
        &fbCount
    );

    if (!fbConfigs || fbCount == 0) {
        throw std::runtime_error("No proper framebuffers available");
    }

    // Get the visual from our chosen framebuffer.
    this->visual = ::glXGetVisualFromFBConfig(this->display, fbConfigs[0]);

    // Create the GLX pixel buffer.
    this->glxPixelBuffer = ::glXCreatePbuffer(
        this->display,
        fbConfigs[0],
        pbAttribs
    );

    if (!this->glxPixelBuffer) {
        throw std::runtime_error("Failed to initialize GLX pixel buffer");
    }

    // Create the context.
    this->ctx = glXCreateContextAttribsARB(
        this->display,
        fbConfigs[0],
        0,
        true,
        ctxAttribs
    );

    if (!this->ctx) {
        throw std::runtime_error("Failed to initialize graphics context");
    }

    // Wait for X to throw any errors available.
    ::XSync(this->display, false);

    // Immediately enable off-screen rendering.
    this->use();
    this->check("Cannot create graphics context");

    // Initialize GLEW.
    ::glewExperimental = true;
    this->status = ::glewInit();
    if (this->status != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Configure OpenGL.
    ::glEnable(GL_VERTEX_ARRAY);
    this->check("Cannot enable GL vertex arrays");

    ::glEnable(GL_DEPTH_TEST);
    this->check("Cannot enable GL depth test");

    ::glDepthFunc(GL_LESS);
    this->check("Cannot set GL depth test function");

    ::glEnable(GL_BLEND);
    this->check("Cannot enable GL blending");

    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    this->check("Cannot set GL blending function");
}

// Destructor.
randar::GraphicsContext::~GraphicsContext()
{
    for (auto resource : this->resources) {
        delete resource;
    }

    ::glXDestroyPbuffer(this->display, this->glxPixelBuffer);
    ::glXDestroyContext(this->display, this->ctx);
    ::XFree(this->visual);
    ::XCloseDisplay(this->display);
}

// Makes this context current without considering a window.
void randar::GraphicsContext::use()
{
    this->check("Uncaught GL error");

    bool success = ::glXMakeCurrent(
        this->display,
        this->glxPixelBuffer,
        this->ctx
    );

    this->check("Cannot switch graphics context");
    if (!success) {
        throw std::runtime_error("Failed to switch graphics context");
    }
}

// Makes this context and a window current.
void randar::GraphicsContext::use(randar::Window& window)
{
    bool success = ::glXMakeCurrent(
        this->display,
        window.glx(),
        this->ctx
    );

    if (!success) {
        throw std::runtime_error("Failed to switch graphics context");
    }
}

// Waits for any queued OpenGL commands to be completed.
void randar::GraphicsContext::sync()
{
    ::glFinish();
}

// Checks for any errors reported by OpenGL.
void randar::GraphicsContext::check(const std::string& message)
{
    static std::map<GLenum, std::string> errorDescriptions = {
        { GL_INVALID_ENUM, "Invalid enum passed to GL" },
        { GL_INVALID_VALUE, "Invalid value passed to GL" },
        { GL_INVALID_OPERATION, "GL operation not valid" },
        { GL_INVALID_FRAMEBUFFER_OPERATION, "Invalid GL framebuffer operation" },
        { GL_OUT_OF_MEMORY, "Out of memory" }
    };

    this->status = ::glGetError();
    if (status == GL_NO_ERROR) {
        return;
    }

    std::string description = errorDescriptions[this->status];
    if (description.empty()) {
        description = "Unknown GL error #" + std::to_string(this->status);
    }

    // Clear the error queue.
    uint32_t additionalErrorCount = 0;
    while ((this->status =::glGetError()) != GL_NO_ERROR) {
        additionalErrorCount++;
    }

    if (additionalErrorCount) {
        description += "(+ "
                     + std::to_string(additionalErrorCount)
                     + " unchecked)";
    }

    throw std::runtime_error(message + ": " + description);
}

// Associates and unassociates a resources with this context.
void randar::GraphicsContext::associate(randar::GraphicsContextResource& r)
{
    if (this->resources.count(&r)) {
        throw std::runtime_error("Context is already associated with resource");
    }

    if (r.ctx) {
        throw std::runtime_error(
            "Resource is already associated with "
            + std::string(r.ctx == this ? "this" : "another")
            + " context"
        );
    }

    this->resources.insert(&r);
    r.ctx = this;
}

void randar::GraphicsContext::unassociate(randar::GraphicsContextResource& r)
{
    if (!this->resources.erase(&r)) {
        throw std::runtime_error("Resource is not associated with context");
    }
}

bool randar::GraphicsContext::isAssociated(randar::GraphicsContextResource& r)
{
    return this->resources.count(&r);
}

// Resource creators.
randar::Framebuffer& randar::GraphicsContext::framebuffer()
{
    return *new Framebuffer(*this);
}

randar::Texture& randar::GraphicsContext::texture(
    uint32_t width,
    uint32_t height,
    const std::string& type)
{
    return *new Texture(*this, width, height, type);
}

randar::Window& randar::GraphicsContext::window(uint32_t width, uint32_t height)
{
    return *new randar::Window(*this, width, height);
}

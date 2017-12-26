#include <map>
#include <randar/System/GraphicsContextResource.hpp>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Render/Geometry.hpp>
#include <randar/Render/ShaderProgram.hpp>
#include <randar/Render/Light/Spotlight.hpp>
#include <randar/System/Monitor.hpp>
#include <randar/System/Window.hpp>
#include <randar/System/FbConfig.hpp>

// Allows us to pass attributes while creating a context.
typedef GLXContext (*glXCreateContextAttribsARBProc)(
    Display*,
    GLXFBConfig,
    GLXContext,
    Bool,
    const int*
);

// X error handler.
static int xErrorHandler(Display *dpy, XErrorEvent *ev)
{
    throw std::runtime_error("X error");
    return 0;
}

// OpenGL debug message handler.
void graphicsContextDebugHandler(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cout << std::string(message, length) << std::endl;
}

// Constructor.
randar::GraphicsContext::GraphicsContext()
{
    // Register the X error handler.
    ::XSetErrorHandler(xErrorHandler);

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
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        None
    };

    int ctxAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 5,
        None
    };

    // Get a local X display.
    this->display = ::XOpenDisplay(0);
    if (!this->display) {
        throw std::runtime_error("Cannot create X display connection");
    }

    // Unassign any active context.
    ::glXMakeCurrent(this->display, None, NULL);

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

    // Check framebuffer configuration.
    FbConfig fbc(this->display, fbConfigs[0]);
    if (!fbc.renderable) {
        throw std::runtime_error("No renderable framebuffer config available");
    }

    if (!fbc.doublebuffer) {
        throw std::runtime_error("Double buffering not available");
    }

    if (fbc.visualType != GLX_TRUE_COLOR) {
        throw std::runtime_error("True color visual not available");
    }

    // Get the visual from our chosen configuration.
    this->visual = ::glXGetVisualFromFBConfig(this->display, fbConfigs[0]);
    if (!this->visual) {
        throw std::runtime_error("Failed to get X visual information");
    }

    // Create the context.
    this->ctx = glXCreateContextAttribsARB(
        this->display,
        fbConfigs[0],
        0,
        true,
        ctxAttribs
    );

    // Wait for X to throw any errors available.
    ::XSync(this->display, false);
    if (!this->ctx) {
        throw std::runtime_error("Failed to create graphics context");
    }

    // Ensure we've created a direct rendering context.
    if (!::glXIsDirect(this->display, this->ctx)) {
        throw std::runtime_error("Graphics context is not direct");
    }

    // Immediately enable off-screen rendering.
    this->use();
    this->check("Cannot create graphics context");
    if (!this->isCurrent()) {
        throw std::runtime_error("Failed to make context current");
    }

    // Initialize GLEW.
    ::glewExperimental = true;
    this->status = ::glewInit();
    if (this->status != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Enable OpenGL debug mode, ignoring non-errors.
    ::glEnable(GL_DEBUG_OUTPUT);
    ::glDebugMessageControl(
        GL_DONT_CARE,
        GL_DONT_CARE,
        GL_DEBUG_SEVERITY_NOTIFICATION,
        0,
        nullptr,
        GL_FALSE
    );

    ::glDebugMessageCallback(graphicsContextDebugHandler, nullptr);
    this->check("Cannot enable OpenGL debug mode");

    // Ensure the context is responsive.
    this->sync();
    try {
        this->version();
    } catch (std::runtime_error& e) {
        this->check("Failed to query graphics context version");
        throw std::runtime_error("Corrupted graphics context");
    }

    // Enable basic OpenGL behaviors.
    ::glEnable(GL_DEPTH_TEST);
    this->check("Cannot enable GL depth test");

    ::glDepthFunc(GL_LESS);
    this->check("Cannot set GL depth test function");

    ::glEnable(GL_BLEND);
    this->check("Cannot enable GL blending");

    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    this->check("Cannot set GL blending function");

    ::glDisable(GL_CULL_FACE);
    this->check("Cannot disable face culling");
}

// Destructor.
randar::GraphicsContext::~GraphicsContext()
{
    // Destroy resources owned by this context.
    for (auto resource : this->ownedResources) {
        this->resources.erase(resource);
        delete resource;
    }

    // Unassociate resources associated, but not owned, by this context.
    for (auto resource : this->resources) {
        resource->unassociateContext();
    }

    // Destroy default resources.
    for (auto item : this->dShaders) {
        delete item.second;
    }
    delete this->dShaderProgram;

    // Destroy GLX objects and free X resources.
    ::glXDestroyContext(this->display, this->ctx);
    ::XFree(this->visual);
    ::XCloseDisplay(this->display);
}

// Queries the version of OpenGL being used.
std::string randar::GraphicsContext::version()
{
    this->use();

    const GLubyte* str = ::glGetString(GL_VERSION);
    this->check("Cannot retrieve OpenGL version");

    if (!str) {
        throw std::runtime_error("Empty context response");
    }

    return std::string(reinterpret_cast<const char*>(str));
}

// Makes this context current without considering a window.
void randar::GraphicsContext::use()
{
    if (this->isCurrent()) {
        return;
    }

    bool success = ::glXMakeCurrent(
        this->display,
        None,
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
    if (this != &window.context()) {
        throw std::runtime_error("Window is not associated with this context");
    }

    if (this->isCurrent(window)) {
        return;
    }

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

    this->use();
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

// Whether the context is current.
bool randar::GraphicsContext::isCurrent()
{
    return ::glXGetCurrentContext() == this->ctx;
}

bool randar::GraphicsContext::isCurrent(randar::Window& window)
{
    return ::glXGetCurrentDrawable() == window.glx();
}

// Associates and unassociates a resources with this context.
void randar::GraphicsContext::associate(randar::GraphicsContextResource& r)
{
    if (this->resources.count(&r)) {
        return;
    }

    if (r.ctx != this) {
        throw std::runtime_error(
            "Resource is already associated with another context"
        );
    }

    this->resources.insert(&r);
}

void randar::GraphicsContext::unassociate(randar::GraphicsContextResource& r)
{
    this->resources.erase(&r);
}

// Checks if a resource is associated with the context.
bool randar::GraphicsContext::isAssociated(randar::GraphicsContextResource& r)
{
    return this->resources.count(&r);
}

// Counts the resources associated with this context.
unsigned int randar::GraphicsContext::resourceCount() const
{
    return this->resources.size();
}

// Resource creators.
randar::FloatArrayBuffer& randar::GraphicsContext::floatArrayBuffer()
{
    randar::FloatArrayBuffer *fab = new FloatArrayBuffer(*this);
    this->ownedResources.insert(fab);
    return *fab;
}

randar::IndexBuffer& randar::GraphicsContext::indexBuffer()
{
    randar::IndexBuffer *ib = new IndexBuffer(*this);
    this->associate(*ib);
    return *ib;
}

randar::VertexBuffer& randar::GraphicsContext::vertexBuffer()
{
    randar::VertexBuffer *vb = new VertexBuffer(*this);
    this->associate(*vb);
    return *vb;
}

randar::Geometry& randar::GraphicsContext::geometry()
{
    randar::Geometry *geo = new Geometry(*this);
    this->associate(*geo);
    return *geo;
}

randar::Renderbuffer& randar::GraphicsContext::renderbuffer(
    uint32_t width,
    uint32_t height,
    const std::string& type)
{
    randar::Renderbuffer* rb = new Renderbuffer(*this, width, height, type);
    this->associate(*rb);
    return *rb;
}

randar::Framebuffer& randar::GraphicsContext::framebuffer()
{
    randar::Framebuffer* fb = new Framebuffer(*this);
    this->associate(*fb);
    return *fb;
}

randar::Texture& randar::GraphicsContext::texture(
    uint32_t width,
    uint32_t height,
    const std::string& type)
{
    randar::Texture* t = new Texture(*this, width, height, type);
    this->associate(*t);
    return *t;
}

randar::Window& randar::GraphicsContext::window(uint32_t width, uint32_t height)
{
    randar::Window* w = new randar::Window(*this, width, height);
    this->associate(*w);
    return *w;
}

randar::Monitor& randar::GraphicsContext::monitor(randar::Geometry& geo)
{
    randar::Monitor* m = new randar::Monitor(*this, geo);
    this->associate(*m);
    return *m;
}

randar::Spotlight& randar::GraphicsContext::spotlight()
{
    randar::Spotlight* s = new randar::Spotlight(*this);
    this->associate(*s);
    return *s;
}

// Default resources.
randar::Shader& randar::GraphicsContext::defaultShader(randar::ShaderType type)
{
    if (!this->dShaders.count(type)) {
        this->dShaders[type] = new Shader(*this);
        this->dShaders[type]->initialize(
            type,
            Shader::defaultCode(type)
        );
    }

    return *this->dShaders[type];
}

randar::ShaderProgram& randar::GraphicsContext::defaultShaderProgram()
{
    if (!this->dShaderProgram) {
        this->dShaderProgram = new ShaderProgram(*this);
        this->dShaderProgram->attach(this->defaultShader(ShaderType::VERTEX));
        this->dShaderProgram->attach(this->defaultShader(ShaderType::FRAGMENT));
    }

    return *this->dShaderProgram;
}

std::string randar::GraphicsContext::description()
{
    return "[GraphicsContext | OpenGL " + this->version() + "]";
}

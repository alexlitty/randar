#include <randar/System/GraphicsContext.hpp>
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
        GLX_DOUBLEBUFFER, false,

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

    // Immediately enable off-screen rendering.
    this->use();

    // Initialize glew.
    ::glewExperimental = true;
    GLenum status = ::glewInit();
    if (status != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Configure OpenGL.
    ::glEnable(GL_VERTEX_ARRAY);
    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LESS);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Destructor.
randar::GraphicsContext::~GraphicsContext()
{
    ::glXMakeCurrent(
        this->display,
        None,
        None
    );

    for (auto window : this->windows) {
        delete window;
    }

    ::glXDestroyPbuffer(this->display, this->glxPixelBuffer);
    ::glXDestroyContext(this->display, this->ctx);
    ::XFree(this->visual);
    ::XCloseDisplay(this->display);
}

// Makes this context current without considering a window.
void randar::GraphicsContext::use()
{
    bool success = ::glXMakeCurrent(
        this->display,
        this->glxPixelBuffer,
        this->ctx
    );

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

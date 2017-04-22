#include <randar/System/GraphicsContext.hpp>
#include <randar/System/Window.hpp>

// Constructs the definition of a window.
randar::Window::Window(
    randar::GraphicsContext& context,
    uint32_t width,
    uint32_t height
) :
  randar::Dimensional2<uint32_t>(width, height),
  ctx(context)
{
    ::XSetWindowAttributes swa;

    swa.event_mask = ExposureMask | KeyPressMask;
    swa.colormap = ::XCreateColormap(
        ctx.display,
        DefaultRootWindow(ctx.display),
        ctx.visual->visual,
        AllocNone
    );

    this->handle = ::XCreateWindow(
        ctx.display,
        DefaultRootWindow(ctx.display),
        0,
        0,
        width,
        height,
        0,
        ctx.visual->depth,
        InputOutput,
        ctx.visual->visual,
        CWColormap | CWEventMask,
        &swa
    );

    this->glxWindow = ::glXCreateWindow(
        ctx.display,
        ctx.fbConfigs[0],
        this->handle,
        nullptr
    );

    ::XSync(ctx.display, false);
    ::XMapWindow(ctx.display, this->handle);
}

// Destructor.
randar::Window::~Window()
{
    ::glXDestroyWindow(this->ctx.display, this->glxWindow);
    ::XDestroyWindow(this->ctx.display, this->handle);
}

// Retrieves the associated context.
randar::GraphicsContext& randar::Window::context()
{
    return this->ctx;
}

// Retrieves the native window handle.
::Window randar::Window::native()
{
    return this->handle;
}

// Retrieves the GLX window handle.
::GLXWindow randar::Window::glx()
{
    return this->glxWindow;
}

// Makes this window and its associated context current.
void randar::Window::use()
{
    this->ctx.use(*this);
}

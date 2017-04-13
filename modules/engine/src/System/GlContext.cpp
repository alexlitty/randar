#include <stdexcept>
#include <randar/System/GlContext.hpp>

randar::GlContext::GlContext()
{
    static int attribs[] = {
        GLX_X_RENDERABLE, true,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        GLX_DOUBLEBUFFER, true,
        None
    };

    ::Display *display = ::XOpenDisplay(nullptr);
    if (!display) {
        throw std::runtime_error("Failed to open X display");
    }

    int fbcount;
    ::GLXFBConfig *fbc = ::glXChooseFBConfig(
        display,
        DefaultScreen(display),
        attribs,
        &fbcount);
    if (fbcount == 0) {
        throw std::runtime_error("No framebuffers available");
    }

    ::XVisualInfo *vi = ::glXGetVisualFromFBConfig(display, fbc[0]);
    if (!vi) {
        throw std::runtime_error("No appropriate visual found");
    }

    ::GLXContext ctx = ::glXCreateContext(display, vi, nullptr, true);
    if (!ctx) {
        throw std::runtime_error("Failed to create GLX context");
    }

    ::glXMakeCurrent(display, RootWindow(display, vi->screen), ctx);
}

randar::GlContext::GlContext(const GlContext& other)
{

}

randar::GlContext::~GlContext()
{

}

randar::GlContext& randar::GlContext::operator =(const randar::GlContext& other)
{

}

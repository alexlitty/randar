#include <stdexcept>
#include <randar/System/GlContext.hpp>

// Default constructor.
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
        GLX_DOUBLEBUFFER, false,
        None
    };

    this->display = ::XOpenDisplay(nullptr);
    if (!this->display) {
        throw std::runtime_error("Failed to open X display");
    }

    int fbcount;
    ::GLXFBConfig *fbc = ::glXChooseFBConfig(
        this->display,
        DefaultScreen(this->display),
        attribs,
        &fbcount);
    if (fbcount == 0) {
        throw std::runtime_error("No framebuffers available");
    }

    this->visualInfo = ::glXGetVisualFromFBConfig(this->display, fbc[0]);
    if (!this->visualInfo) {
        throw std::runtime_error("No appropriate visual found");
    }

    this->context = ::glXCreateContext(this->display, this->visualInfo, nullptr, true);
    if (!this->context) {
        throw std::runtime_error("Failed to create GLX context");
    }

    ::XFree(fbc);
}

// Dummy copy constructor.
randar::GlContext::GlContext(const GlContext& other)
{
    *this = other;
}

// Destructor.
randar::GlContext::~GlContext()
{
    ::glXDestroyContext(this->display, this->context);
    ::XFree(this->display);
    ::XFree(this->visualInfo);
}

// Makes this context current.
void randar::GlContext::use() {
    ::glXMakeCurrent(this->display, RootWindow(this->display, this->visualInfo->screen), this->context);
}

// Dummy assignment operator.
randar::GlContext& randar::GlContext::operator =(const randar::GlContext& other)
{
    throw std::runtime_error("GlContext may not be copied");
}

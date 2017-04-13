#include <stdexcept>
#include <randar/System/GlContext.hpp>

randar::GlContext::GlContext()
{
    ::Display *display = ::XOpenDisplay(nullptr);
    if (!display) {
        throw std::runtime_error("Failed to open X display");
    }

    static int visual_attribs[] = {
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

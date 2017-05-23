#include <stdexcept>
#include <randar/System/FbConfig.hpp>

// FbAttributes constructor.
randar::FbAttributes::FbAttributes()
//: raw(nullptr)
{

}

// FbAttributes destructor.
randar::FbAttributes::~FbAttributes()
{
    //delete[] this->raw;
}

// Generates an array of the attributes for GLX operations.
int* randar::FbAttributes::data()
{
    this->raw = {
        GLX_X_RENDERABLE, this->renderable,

        GLX_X_VISUAL_TYPE, this->visualType,
        GLX_DRAWABLE_TYPE, this->drawableType,

        GLX_DOUBLEBUFFER, this->doublebuffer,

        GLX_RED_SIZE, this->redSize,
        GLX_GREEN_SIZE, this->greenSize,
        GLX_BLUE_SIZE, this->blueSize,
        GLX_ALPHA_SIZE, this->alphaSize,

        GLX_DEPTH_SIZE, this->depthSize,
        GLX_STENCIL_SIZE, this->stencilSize,
        None
    };

    return this->raw.data();
}

// FbConfig constructor.
randar::FbConfig::FbConfig(Display* initDisplay, ::GLXFBConfig& initGlx)
: display(initDisplay),
  glx(initGlx)
{
    this->query(GLX_X_RENDERABLE, this->renderable);

    this->query(GLX_X_VISUAL_TYPE, this->visualType);
    this->query(GLX_DRAWABLE_TYPE, this->drawableType);

    this->query(GLX_DOUBLEBUFFER, this->doublebuffer);

    this->query(GLX_RED_SIZE, this->redSize);
    this->query(GLX_GREEN_SIZE, this->greenSize);
    this->query(GLX_BLUE_SIZE, this->blueSize);
    this->query(GLX_ALPHA_SIZE, this->alphaSize);

    this->query(GLX_DEPTH_SIZE, this->depthSize);
    this->query(GLX_STENCIL_SIZE, this->stencilSize);
}

// Queries GLX for an attribute.
void randar::FbConfig::query(int attribute, bool& value)
{
    int boolAsInt;
    this->query(attribute, boolAsInt);
    value = static_cast<bool>(boolAsInt);
}

void randar::FbConfig::query(int attribute, int& value)
{
    int r = ::glXGetFBConfigAttrib(this->display, this->glx, attribute, &value);

    if (r == GLX_NO_EXTENSION) {
        throw std::runtime_error("Using unsupported GLX extension");
    }

    if (r == GLX_BAD_ATTRIBUTE) {
        throw std::runtime_error("Using bad GLX attribute");
    }
}

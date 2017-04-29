#include <randar/System/GlNamedResource.hpp>

// Default constructor.
randar::GlNamedResource::GlNamedResource()
: glName(0)
{

}

// Destructor.
randar::GlNamedResource::~GlNamedResource()
{

}

// Gets the GL name for this resource.
GLuint randar::GlNamedResource::getGlName() const
{
    return this->glName;
}

#include <randar/Render/Renderbuffer.hpp>

const randar::Resource::Type randar::Renderbuffer::type = randar::Resource::RENDERBUFFER;
randar::Resource::Type randar::Renderbuffer::getType() const
{
    return this->type;
}



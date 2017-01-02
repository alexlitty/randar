#include <randar/Render/IndexBuffer.hpp>

const randar::Resource::Type randar::IndexBuffer::type = randar::Resource::INDEXBUFFER;
randar::Resource::Type randar::IndexBuffer::getType() const
{
    return this->type;
}

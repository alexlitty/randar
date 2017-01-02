#include <randar/Render/VertexBuffer.hpp>

const randar::Resource::Type randar::VertexBuffer::type = randar::Resource::VERTEXBUFFER;
randar::Resource::Type randar::VertexBuffer::getType() const
{
    return this->type;
}

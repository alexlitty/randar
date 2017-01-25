#include <randar/Render/VertexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::VertexArray::initialize()
{
    this->gpu.initialize(*this);
}

void randar::VertexArray::destroy()
{
    this->gpu.destroy(*this);
}

void randar::VertexBuffer::initialize()
{
    this->gpu.initialize(*this);
}

void randar::VertexBuffer::destroy()
{
    this->gpu.destroy(*this);
}

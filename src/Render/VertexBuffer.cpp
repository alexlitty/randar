#include <randar/Render/VertexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::VertexArray::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

void randar::VertexArray::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}

void randar::VertexBuffer::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

void randar::VertexBuffer::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}

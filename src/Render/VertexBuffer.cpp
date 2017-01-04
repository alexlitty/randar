#include <randar/Render/VertexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::VertexArray::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
    this->initialized = true;
}

void randar::VertexArray::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
    this->initialized = false;
}

void randar::VertexBuffer::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
    this->initialized = true;
}

void randar::VertexBuffer::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
    this->initialized = false;
}

#include <randar/Render/IndexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::IndexBuffer::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
    this->initialized = true;
}

void randar::IndexBuffer::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
    this->initialized = false;
}

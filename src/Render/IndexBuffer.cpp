#include <randar/Render/IndexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::IndexBuffer::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

void randar::IndexBuffer::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}

#include <randar/Render/IndexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::IndexBuffer::initialize()
{
    this->gpu.initialize(*this);
}

void randar::IndexBuffer::destroy()
{
    this->gpu.destroy(*this);
}

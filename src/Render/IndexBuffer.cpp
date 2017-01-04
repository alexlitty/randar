#include <randar/Render/IndexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::IndexBuffer::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
}

void randar::IndexBuffer::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
}

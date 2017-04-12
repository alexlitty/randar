#include <randar/Render/IndexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

randar::IndexBuffer::IndexBuffer()
{

}

randar::IndexBuffer::IndexBuffer(const IndexBuffer& other)
{
    *this = other;
}

void randar::IndexBuffer::initialize()
{
    this->gpu.initialize(*this);
}

void randar::IndexBuffer::destroy()
{
    this->gpu.destroy(*this);
}

randar::IndexBuffer& randar::IndexBuffer::operator =(const IndexBuffer& other)
{
    this->glName = other.glName;
}

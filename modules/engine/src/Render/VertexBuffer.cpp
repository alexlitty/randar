#include <randar/Render/VertexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

randar::VertexArray::VertexArray()
{

}

randar::VertexArray::VertexArray(const randar::VertexArray& other)
{
    *this = other;
}

void randar::VertexArray::initialize()
{
    this->gpu.initialize(*this);
}

void randar::VertexArray::destroy()
{
    this->gpu.destroy(*this);
}

randar::VertexArray& randar::VertexArray::operator =(const randar::VertexArray& other)
{
    this->glName = other.glName;
}

randar::VertexBuffer::VertexBuffer()
{

}

randar::VertexBuffer::VertexBuffer(const randar::VertexBuffer& other)
{
    *this = other;
}

void randar::VertexBuffer::initialize()
{
    this->gpu.initialize(*this);
}

void randar::VertexBuffer::destroy()
{
    this->gpu.destroy(*this);
}

randar::VertexBuffer& randar::VertexBuffer::operator =(const randar::VertexBuffer& other)
{
    this->glName = other.glName;
}

#include <randar/Render/VertexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

randar::VertexArray::VertexArray(randar::Gpu& initGpu)
: randar::GpuResource(&initGpu)
{

}

randar::VertexArray::VertexArray(const randar::VertexArray& other)
: randar::VertexArray(*other.gpu)
{
    *this = other;
}

void randar::VertexArray::initialize()
{
    this->gpu->initialize(*this);
}

void randar::VertexArray::destroy()
{
    this->gpu->destroy(*this);
}

randar::VertexArray& randar::VertexArray::operator =(const randar::VertexArray& other)
{
    this->glName = other.glName;
    return *this;
}

randar::VertexBuffer::VertexBuffer(randar::Gpu& initGpu)
: randar::GpuResource(&initGpu),
  vertexArray(initGpu)
{

}

randar::VertexBuffer::VertexBuffer(const randar::VertexBuffer& other)
: randar::VertexBuffer(*other.gpu)
{
    *this = other;
}

void randar::VertexBuffer::initialize()
{
    this->gpu->initialize(*this);
}

void randar::VertexBuffer::destroy()
{
    this->gpu->destroy(*this);
}

randar::VertexBuffer& randar::VertexBuffer::operator =(const randar::VertexBuffer& other)
{
    this->glName = other.glName;
    return *this;
}

#include <randar/Render/IndexBuffer.hpp>
#include <randar/Engine/Gpu.hpp>

randar::IndexBuffer::IndexBuffer(randar::Gpu& initGpu)
: randar::GpuResource(&initGpu)
{

}

randar::IndexBuffer::IndexBuffer(const IndexBuffer& other)
: randar::GpuResource(other.gpu)
{
    *this = other;
}

randar::IndexBuffer& randar::IndexBuffer::operator =(const IndexBuffer& other)
{
    this->gpu = other.gpu;
    this->glName = other.glName;
    return *this;
}

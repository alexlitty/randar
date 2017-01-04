#include <randar/Render/Mesh.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::Mesh::initialize(randar::Gpu& gpu)
{
    gpu.initialize(this->vertexBuffer);
    gpu.initialize(this->indexBuffer);
    this->initialized = true;
}

void randar::Mesh::destroy(randar::Gpu& gpu)
{
    gpu.destroy(this->vertexBuffer);
    gpu.destroy(this->indexBuffer);
    this->initialized = false;
}

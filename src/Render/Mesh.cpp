#include <randar/Render/Mesh.hpp>
#include <randar/Engine/Gpu.hpp>

void randar::Mesh::initialize()
{
    this->gpu.initialize(this->vertexBuffer);
    this->gpu.initialize(this->indexBuffer);
    this->initialized = true;
}

void randar::Mesh::destroy()
{
    this->gpu.destroy(this->vertexBuffer);
    this->gpu.destroy(this->indexBuffer);
    this->initialized = false;
}

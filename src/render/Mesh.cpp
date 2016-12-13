#include <randar/render/Mesh.hpp>

randar::Mesh::Mesh()
{
    ::glGenBuffers(1, &this->indexBuffer);
}

randar::Mesh::~Mesh()
{
    ::glDeleteBuffers(1, &this->indexBuffer);
}

void randar::Mesh::draw() const
{

}

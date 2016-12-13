#include <randar/render/Mesh.hpp>

randar::Mesh::Mesh()
{
    ::glGenBuffers(1, &this->indexBuffer);
}

randar::Mesh::~Mesh()
{
    ::glDeleteBuffers(1, &this->indexBuffer);
}

void randar::Mesh::bind() const
{
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
}

void randar::Mesh::send() const
{
    this->bind();
    ::glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        this->indices.size() * sizeof(unsigned int),
        &indices[0],
        GL_STATIC_DRAW
    );
}

void randar::Mesh::draw() const
{
    this->vertices.bind();
    this->bind();
    ::glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
}

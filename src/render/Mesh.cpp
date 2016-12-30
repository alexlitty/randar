#include <randar/render/Mesh.hpp>

randar::Mesh::Mesh()
{
    ::glGenBuffers(1, &this->indexBuffer);
}

randar::Mesh::Mesh(const randar::Mesh& other)
: randar::Mesh::Mesh()
{
    this->vertices = other.vertices;
    this->indices = other.indices;
    this->send();
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

void randar::Mesh::appendVertex(const randar::Vector& position, const randar::Color& color)
{
    this->appendVertex(Vertex(position, color));
}

void randar::Mesh::appendVertex(const randar::Vertex& vertex)
{
    this->vertices.append(vertex);
}

void randar::Mesh::appendFace(unsigned int a, unsigned int b, unsigned int c)
{
    this->indices.push_back(a);
    this->indices.push_back(b);
    this->indices.push_back(c);
}

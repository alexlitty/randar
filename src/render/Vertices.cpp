#include <randar/render/Vertices.hpp>

randar::Vertices::Vertices()
{
    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);

    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    for (auto attribute : Vertex::attributes) {
        glEnableVertexAttribArray(attribute.location);
        glVertexAttribPointer(
            attribute.location,
            attribute.size,
            GL_FLOAT,
            GL_FALSE,
            Vertex::stride,
            static_cast<char*>(0) + attribute.offset
        );
    }
}

randar::Vertices::~Vertices()
{
    glDeleteBuffers(1, &this->vertexBuffer);
    glDeleteVertexArrays(1, &this->vertexArray);
}

void randar::Vertices::send()
{
    unsigned int dataSize = vertices.size() * Vertex::size;
    GLfloat *data = new float[dataSize];
    for (auto vertex : this->vertices) {
        vertex.appendTo(data);
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    delete[] data;
}

void randar::Vertices::append(randar::Vertex &vertex)
{
    this->vertices.push_back(vertex);
}

void randar::Vertices::draw() const
{
    glBindVertexArray(this->vertexArray);
    if (!this->vertices.size()) {
        return;
    }
}

randar::Vertex& randar::Vertices::operator[](unsigned int index)
{
    return this->vertices[index];
}

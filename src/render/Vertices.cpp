#include <randar/render/Vertices.hpp>

randar::Vertices::Vertices(GLenum initPrimitive)
: primitive(initPrimitive)
{
    ::glGenVertexArrays(1, &this->vertexArray);
    ::glBindVertexArray(this->vertexArray);

    ::glGenBuffers(1, &this->vertexBuffer);
    ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    unsigned int stride = 7 * sizeof(GLfloat);

    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)0
    );

    ::glEnableVertexAttribArray(1);
    ::glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(3 * sizeof(GLfloat))
    );
}

randar::Vertices::~Vertices()
{
    glDeleteBuffers(1, &this->vertexBuffer);
    glDeleteVertexArrays(1, &this->vertexArray);
}

// Sets the interpretation of the vertices.
void randar::Vertices::setPrimitive(GLenum primitive)
{
    this->primitive = primitive;
}

void randar::Vertices::send()
{
    unsigned int dataSize = this->vertices.size() * 7;
    GLfloat *data = new GLfloat[dataSize], *subdata;
    for (unsigned int i = 0; i < this->vertices.size(); i++) {
        subdata = &data[i * 7];
        auto vertex = this->vertices[i];
        vertex.appendTo(subdata);
    }

    ::glBindVertexArray(this->vertexArray);
    ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    ::glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dataSize, data, GL_STATIC_DRAW);

    delete[] data;
}

void randar::Vertices::append(randar::Vertex &vertex)
{
    this->vertices.push_back(vertex);
}

void randar::Vertices::draw() const
{
    unsigned int vertexCount = this->vertices.size();
    if (!vertexCount) {
        return;
    }

    glDrawArrays(this->primitive, 0, vertexCount);
}

randar::Vertex& randar::Vertices::operator[](unsigned int index)
{
    return this->vertices[index];
}

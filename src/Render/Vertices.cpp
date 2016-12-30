#include <randar/Render/Vertices.hpp>

randar::Vertices::Vertices(GLenum initPrimitive)
: primitive(initPrimitive)
{
    ::glGenVertexArrays(1, &this->vertexArray);
    ::glBindVertexArray(this->vertexArray);

    ::glGenBuffers(1, &this->vertexBuffer);
    ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    unsigned int stride = 17 * sizeof(GLfloat);

    // Position.
    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)0
    );

    // Color.
    ::glEnableVertexAttribArray(1);
    ::glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(3 * sizeof(GLfloat))
    );

    // Bone index.
    ::glEnableVertexAttribArray(2);
    ::glVertexAttribPointer(
        2,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(7 * sizeof(GLfloat))
    );

    // Bone weights.
    ::glEnableVertexAttribArray(3);
    ::glVertexAttribPointer(
        3,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(11 * sizeof(GLfloat))
    );

    // Texture coordinates.
    ::glEnableVertexAttribArray(4);
    ::glVertexAttribPointer(
        4,
        2,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(15 * sizeof(GLfloat))
    );
}

randar::Vertices::Vertices(const Vertices& other)
: Vertices::Vertices(other.primitive)
{
    this->vertices = other.vertices;
    this->send();
}

randar::Vertices::~Vertices()
{
    ::glDeleteBuffers(1, &this->vertexBuffer);
    ::glDeleteVertexArrays(1, &this->vertexArray);
}

// Sets the interpretation of the vertices.
void randar::Vertices::setPrimitive(GLenum primitive)
{
    this->primitive = primitive;
}

// Clears all vertices.
void randar::Vertices::clear()
{
    this->vertices.clear();
}

// Retrieves the number of vertices in this collection.
unsigned int randar::Vertices::getVertexCount() const
{
    return this->vertices.size();
}

// Binds the underlying vertex array object to the GPU.
void randar::Vertices::bind() const
{
    ::glBindVertexArray(this->vertexArray);
    ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

// Sends this buffer's data to the GPU.
void randar::Vertices::send() const
{
    unsigned int dataSize = this->vertices.size() * 17;
    GLfloat *data = new GLfloat[dataSize], *subdata;
    for (unsigned int i = 0; i < this->vertices.size(); i++) {
        subdata = &data[i * 17];
        auto vertex = this->vertices[i];
        vertex.appendTo(subdata);
    }

    ::glBindVertexArray(this->vertexArray);
    ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    ::glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dataSize, data, GL_STATIC_DRAW);

    delete[] data;
}

void randar::Vertices::append(const randar::Vertex& vertex)
{
    this->vertices.push_back(vertex);
}

randar::Vertex& randar::Vertices::operator[](unsigned int index)
{
    return this->vertices[index];
}

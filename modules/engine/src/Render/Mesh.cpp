#include <randar/Render/Mesh.hpp>

// Constructor.
randar::Mesh::Mesh(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  vertexArrayName(0),
  attributeBufferCount(0),
  positionBufferName(0),
  colorBufferName(0),
  indexBufferName(0)
{
    this->initialize();
}

// Destructor.
randar::Mesh::~Mesh()
{
    this->uninitialize();
}

// Helper functions to create OpenGL buffers.
void randar::Mesh::createBuffer(const std::string& name, GLuint& glName)
{
    ::glGenBuffers(1, &glName);
    this->ctx->check("Cannot generate" + name + " buffer");
    if (!glName) {
        throw std::runtime_error("Failed to generate " + name + " buffer");
    }
}

void randar::Mesh::createAttributeBuffer(
    const std::string& name,
    GLuint& glName,
    GLenum valueType,
    GLboolean valueNormalized,
    GLint valueCount)
{
    this->createBuffer(name, glName);
    ::glBindBuffer(GL_ARRAY_BUFFER, glName);

    ::glEnableVertexAttribArray(this->attributeBufferCount);
    ::glVertexAttribPointer(
        this->attributeBufferCount,
        valueCount,
        valueType,
        valueNormalized,
        0,
        nullptr
    );

    this->attributeBufferCount++;
}

// Initializes the mesh on the associated graphics context.
void randar::Mesh::initialize()
{
    if (this->isInitialized()) {
        return;
    }

    ::glGenVertexArrays(1, &this->vertexArrayName);
    ::glBindVertexArray(this->vertexArrayName);

    this->createAttributeBuffer(
        "position",
        this->positionBufferName,
        GL_FLOAT,
        GL_FALSE,
        3
    );

    this->createAttributeBuffer(
        "color",
        this->colorBufferName,
        GL_FLOAT,
        GL_FALSE,
        4
    );

    this->createBuffer("index", this->indexBufferName);
}

// Uninitializes the mesh from the associated graphics context.
void randar::Mesh::uninitialize()
{
    if (this->ctx) {
        if (this->indexBufferName) {
            ::glDeleteBuffers(1, &this->indexBufferName);
        }

        if (this->colorBufferName) {
            ::glDeleteBuffers(1, &this->colorBufferName);
        }

        if (this->positionBufferName) {
            ::glDeleteBuffers(1, &this->positionBufferName);
        }

        if (this->vertexArrayName) {
            ::glDeleteVertexArrays(1, &this->vertexArrayName);
        }
    }
}

// Whether this mesh is initialized on the associated graphics context.
bool randar::Mesh::isInitialized() const
{
    return this->ctx
        && this->vertexArrayName
        && this->positionBufferName
        && this->colorBufferName
        && this->indexBufferName;
}

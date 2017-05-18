#include <randar/Render/VertexBuffer.hpp>

// Constructor.
randar::VertexBuffer::VertexBuffer(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  positionBuffer(context),
  colorBuffer(context)
{
    this->initialize();
}

// Destructor.
randar::VertexBuffer::~VertexBuffer()
{
    this->uninitialize();
}

// Initializes the vertex buffer on a context.
void randar::VertexBuffer::initialize()
{
    ::glGenVertexArrays(1, &this->vertexArrayName);
    this->ctx->check("Cannot create vertex array");
    if (!this->vertexArrayName) {
        throw std::runtime_error("Failed to create vertex array");
    }

    this->positionBuffer.initialize();
    this->colorBuffer.initialize();

    this->bind();
    this->positionBuffer.bind();
    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    this->colorBuffer.bind();
    ::glEnableVertexAttribArray(1);
    ::glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, 0, nullptr);

    this->ctx->check("Cannot assign vertex attribute pointers");
}

// Uninitializes the vertex buffer from a context.
void randar::VertexBuffer::uninitialize()
{
    if (this->isInitialized()) {
        ::glDeleteVertexArrays(1, &this->vertexArrayName);

        this->positionBuffer.uninitialize();
        this->colorBuffer.uninitialize();
    }
}

// Whether the vertex buffer is initialized on a context.
bool randar::VertexBuffer::isInitialized() const
{
    return this->ctx
        && this->vertexArrayName
        && this->positionBuffer.isInitialized()
        && this->colorBuffer.isInitialized();
}

// Binds the vertex buffer for further operations.
void randar::VertexBuffer::bind()
{
    if (!this->isInitialized()) {
        throw std::runtime_error("Cannot bind uninitialized vertex buffer");
    }

    ::glBindVertexArray(this->vertexArrayName);
}

// Syncs local data to the OpenGL buffers.
void randar::VertexBuffer::sync()
{
    this->positionBuffer.sync();
    this->colorBuffer.sync();
}

// Appends a new vertex.
void randar::VertexBuffer::append(const randar::Vertex& vertex)
{
    this->vertices.push_back(vertex);

    this->positionBuffer.append(vertex.position.x);
    this->positionBuffer.append(vertex.position.y);
    this->positionBuffer.append(vertex.position.z);

    this->colorBuffer.append(vertex.color.r());
    this->colorBuffer.append(vertex.color.g());
    this->colorBuffer.append(vertex.color.b());
    this->colorBuffer.append(vertex.color.a());
}

// Retrieves the vertex at the desired index.
randar::Vertex randar::VertexBuffer::get(uint32_t index) const
{
    if (index >= this->count()) {
        throw std::runtime_error("Vertex index is out of range");
    }

    return this->vertices[index];
}

// Queries the vertex at the desired index in the lower level buffers.
randar::Vertex randar::VertexBuffer::query(uint32_t index)
{
    uint32_t positionIndex = index * 3;
    uint32_t colorIndex    = index * 4;

    return Vertex(
        Vector3(
            this->positionBuffer.query(positionIndex),
            this->positionBuffer.query(positionIndex + 1),
            this->positionBuffer.query(positionIndex + 2)
        ),

        Color(
            this->colorBuffer.query(colorIndex),
            this->colorBuffer.query(colorIndex + 1),
            this->colorBuffer.query(colorIndex + 2),
            this->colorBuffer.query(colorIndex + 3)
        )
    );
}

// Finds the index of a vertex in this collection.
bool randar::VertexBuffer::find(const randar::Vertex& vertex, uint32_t& index)
{
    uint32_t count = this->count();
    for (uint32_t i = 0; i < count; i++) {
        if (this->vertices[i] == vertex) {
            index = i;
            return true;
        }
    }
    return false;
}

// Counts the vertices in this collection.
uint32_t randar::VertexBuffer::count() const
{
    return this->vertices.size();
}

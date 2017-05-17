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
    this->positionBuffer.initialize();
    this->colorBuffer.initialize();
}

// Uninitializes the vertex buffer from a context.
void randar::VertexBuffer::uninitialize()
{
    this->positionBuffer.uninitialize();
    this->colorBuffer.uninitialize();
}

// Whether the vertex buffer is initialized on a context.
bool randar::VertexBuffer::isInitialized() const
{
    return this->positionBuffer.isInitialized()
        && this->colorBuffer.isInitialized();
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
    this->positionBuffer.append(vertex.position.x);
    this->positionBuffer.append(vertex.position.y);
    this->positionBuffer.append(vertex.position.z);

    this->colorBuffer.append(vertex.color.r());
    this->colorBuffer.append(vertex.color.g());
    this->colorBuffer.append(vertex.color.b());
    this->colorBuffer.append(vertex.color.a());
}

//randar::Vertex randar::VertexBuffer::get(uint32_t index) const

#include <randar/Render/VertexBuffer.hpp>

// Constructors.
randar::VertexBuffer::VertexBuffer()
: randar::VertexBuffer(randar::context())
{

}

randar::VertexBuffer::VertexBuffer(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context)
{
    this->initialize();
}

// Assignment.
randar::VertexBuffer::VertexBuffer(const randar::VertexBuffer& other)
: randar::GraphicsContextResource(nullptr)
{
    *this = other;
}

randar::VertexBuffer& randar::VertexBuffer::operator =(const randar::VertexBuffer& other)
{
    this->unassociateContext();
    if (other.ctx) {
        this->context(*other.ctx);
    }

    this->vertices = other.vertices;

    this->positionBuffer = other.positionBuffer;
    this->colorBuffer = other.colorBuffer;
    this->normalBuffer = other.normalBuffer;

    this->textureIdBuffer = other.textureIdBuffer;
    this->textureCoordinateBuffer = other.textureCoordinateBuffer;

    this->jointIndexBuffer = other.jointIndexBuffer;
    this->jointWeightBuffer = other.jointWeightBuffer;

    return *this;
}

// Destructor.
randar::VertexBuffer::~VertexBuffer()
{
    this->uninitialize();
}

// Initializes the vertex buffer on a context.
void randar::VertexBuffer::initialize()
{
    if (!this->ctx) {
        throw std::runtime_error("Vertex buffer not assigned to a context");
    }

    this->bindContext();

    this->positionBuffer.initialize(*this->ctx);
    this->colorBuffer.initialize(*this->ctx);
    this->normalBuffer.initialize(*this->ctx);

    this->textureIdBuffer.initialize(*this->ctx);
    this->textureCoordinateBuffer.initialize(*this->ctx);

    this->jointIndexBuffer.initialize(*this->ctx);
    this->jointWeightBuffer.initialize(*this->ctx);

    ::glGenVertexArrays(1, &this->vertexArrayName);
    this->ctx->check("Cannot create vertex array");
    if (!this->vertexArrayName) {
        throw std::runtime_error("Failed to create vertex array");
    }

    ::glBindVertexArray(this->vertexArrayName);
    ::glEnableVertexAttribArray(0);
    this->positionBuffer.bind();
    ::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    ::glEnableVertexAttribArray(1);
    this->colorBuffer.bind();
    ::glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    ::glEnableVertexAttribArray(2);
    this->normalBuffer.bind();
    ::glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    ::glEnableVertexAttribArray(3);
    this->textureIdBuffer.bind();
    ::glVertexAttribIPointer(3, 1, GL_SHORT, 0, nullptr);

    ::glEnableVertexAttribArray(4);
    this->textureCoordinateBuffer.bind();
    ::glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    ::glEnableVertexAttribArray(5);
    this->jointIndexBuffer.bind();
    ::glVertexAttribIPointer(5, 4, GL_UNSIGNED_SHORT, 0, nullptr);

    ::glEnableVertexAttribArray(6);
    this->jointWeightBuffer.bind();
    ::glVertexAttribIPointer(6, 4, GL_UNSIGNED_BYTE, 0, nullptr);

    this->ctx->check("Cannot assign vertex attribute pointers");
}

// Uninitializes the vertex buffer from a context.
void randar::VertexBuffer::uninitialize()
{
    if (this->isInitialized()) {
        this->bindContext();
        ::glDeleteVertexArrays(1, &this->vertexArrayName);
    }

    this->positionBuffer.uninitialize();
    this->colorBuffer.uninitialize();
    this->normalBuffer.uninitialize();

    this->textureIdBuffer.uninitialize();
    this->textureCoordinateBuffer.uninitialize();

    this->jointIndexBuffer.uninitialize();
    this->jointWeightBuffer.uninitialize();
}

// Whether the vertex buffer is initialized on a context.
bool randar::VertexBuffer::isInitialized() const
{
    return this->ctx
        && this->vertexArrayName;
}

// Binds the vertex buffer for further operations.
void randar::VertexBuffer::bind()
{
    if (!this->isInitialized()) {
        this->initialize();
    }

    this->bindContext();
    ::glBindVertexArray(this->vertexArrayName);
}

// Syncs local data to the OpenGL buffers.
void randar::VertexBuffer::sync()
{
    this->positionBuffer.sync();
    this->colorBuffer.sync();
    this->normalBuffer.sync();

    this->textureIdBuffer.sync();
    this->textureCoordinateBuffer.sync();

    this->jointIndexBuffer.sync();
    this->jointWeightBuffer.sync();
}

// Clears the vertex buffer.
void randar::VertexBuffer::clear()
{
    this->vertices.clear();

    this->positionBuffer.clear();
    this->colorBuffer.clear();
    this->normalBuffer.clear();

    this->textureIdBuffer.clear();
    this->textureCoordinateBuffer.clear();

    this->jointIndexBuffer.clear();
    this->jointWeightBuffer.clear();
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

    this->normalBuffer.append(vertex.normal.x);
    this->normalBuffer.append(vertex.normal.y);
    this->normalBuffer.append(vertex.normal.z);

    this->textureIdBuffer.append(vertex.textureId);

    this->textureCoordinateBuffer.append(vertex.textureCoordinate.u());
    this->textureCoordinateBuffer.append(vertex.textureCoordinate.v());

    uint8_t i = 0;
    for (auto item : vertex.jointWeights) {
        this->jointIndexBuffer.append(item.first);
        this->jointWeightBuffer.append(item.second);
        i++;
    }

    while (i < 4) {
        this->jointIndexBuffer.append(0);
        this->jointWeightBuffer.append(0);
        i++;
    }
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
    uint32_t normalIndex   = index * 3;

    randar::Vertex vertex(
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

    vertex.normal = Vector3(
        this->normalBuffer.query(normalIndex),
        this->normalBuffer.query(normalIndex + 1),
        this->normalBuffer.query(normalIndex + 2)
    );

    vertex.textureId = this->textureIdBuffer.query(index);
    vertex.textureCoordinate.u(this->textureCoordinateBuffer.query(index * 2));
    vertex.textureCoordinate.v(this->textureCoordinateBuffer.query((index * 2)+1));

    for (uint8_t i = 0; i < 4; i++) {
        uint8_t jointIndex = (index * 4) + i;
        vertex.jointWeights[this->jointIndexBuffer.query(jointIndex)] =
            this->jointWeightBuffer.query(jointIndex);
    }

    return vertex;
}

// Whether this collection contains a vertex.
bool randar::VertexBuffer::has(const randar::Vertex& vertex) const
{
    for (auto searchVertex : this->vertices) {
        if (searchVertex == vertex) {
            return true;
        }
    }

    return false;
}

// Finds the index of a vertex in this collection.
bool randar::VertexBuffer::find(const randar::Vertex& vertex, uint32_t& index)
{
    try {
        index = this->find(vertex);
        return true;
    }

    catch (...) {
        return false;
    }
}

uint32_t randar::VertexBuffer::find(const randar::Vertex& vertex)
{
    uint32_t count = this->count();
    for (uint32_t i = 0; i < count; i++) {
        if (this->vertices[i] == vertex) {
            return i;
        }
    }

    throw std::runtime_error("Vertex not found");
}

// Counts the vertices in this collection.
uint32_t randar::VertexBuffer::count() const
{
    return this->vertices.size();
}

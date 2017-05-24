#include <randar/Render/Geometry.hpp>

// Constructors.
randar::Geometry::Geometry()
: randar::GraphicsContextResource(nullptr)
{

}

randar::Geometry::Geometry(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  vertices(context),
  indices(context)
{
    this->initialize();
}

// Assignment.
randar::Geometry::Geometry(const randar::Geometry& other)
: randar::GraphicsContextResource(nullptr)
{
    *this = other;
}

randar::Geometry& randar::Geometry::operator =(const randar::Geometry& other)
{
    this->unassociateContext();
    if (other.ctx) {
        this->context(*other.ctx);
    }

    this->vertices = other.vertices;
    this->indices = other.indices;
    this->primitive = other.primitive;

    return *this;
}

// Destructor.
randar::Geometry::~Geometry()
{
    this->uninitialize();
}

// Initializes the geometry on a context.
void randar::Geometry::initialize()
{
    if (!this->ctx) {
        throw std::runtime_error("Geometry not assigned to a context");
    }

    this->vertices.initialize(*this->ctx);
    this->indices.initialize(*this->ctx);
}

// Uninitializes the geometry from a context.
void randar::Geometry::uninitialize()
{
    this->vertices.uninitialize();
    this->indices.uninitialize();
}

// Whether the geometry is initialized on a context.
bool randar::Geometry::isInitialized()
{
    return this->ctx
        && this->vertices.isInitialized()
        && this->indices.isInitialized();
}

// Syncs local data to OpenGL.
void randar::Geometry::sync()
{
    this->vertices.sync();
    this->indices.sync();
}

// Clears vertices and indices of the geometry.
void randar::Geometry::clear()
{
    this->vertices.clear();
    this->indices.clear();
}

// Adds a vertex to the geometry's available vertices.
uint32_t randar::Geometry::useVertex(const randar::Vertex& vertex)
{
    uint32_t index;
    if (this->vertices.find(vertex, index)) {
        return index;
    }

    index = this->vertices.count();
    this->vertices.append(vertex);
    return index;
}

// Appends a vertex to the geometry shape.
void randar::Geometry::append(const randar::Vertex& vertex)
{
    this->indices.append(this->useVertex(vertex));
}

// Draws the geometry to a framebuffer.
void randar::Geometry::drawTo(
    randar::Framebuffer& fb,
    randar::Transform& transform,
    randar::ShaderProgram& program)
{
    if (!this->ctx || this->ctx != &fb.context()) {
        this->initialize(fb.context());
    }

    this->sync();

    GLenum glPrimitive;
    switch (this->primitive) {
        case randar::Primitive::Point:
            glPrimitive = GL_POINTS;
            break;

        case randar::Primitive::Triangle:
            glPrimitive = GL_TRIANGLES;
            break;

        default:
            throw std::runtime_error("Geometry has unknown primitive type");
            break;
    }

    this->vertices.bind();
    this->indices.bind();
    program.use();

    fb.bind();
    ::glDrawElements(glPrimitive, this->indices.count(), GL_UNSIGNED_INT, nullptr);
    this->ctx->check("Failed to draw geometry to framebuffer");
}

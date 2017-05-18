#include <randar/Render/Geometry.hpp>

randar::Geometry::Geometry(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  vertices(context),
  indices(context)
{
    this->initialize();
}

randar::Geometry::~Geometry()
{
    this->uninitialize();
}

// Initializes the geometry on a context.
void randar::Geometry::initialize()
{
    if (!this->ctx) {
        throw std::runtime_error("Context no longer available");
    }

    this->vertices.initialize();
    this->indices.initialize();
}

// Uninitializes the geometry from a context.
void randar::Geometry::uninitialize()
{
    if (this->isInitialized()) {
        this->vertices.uninitialize();
        this->indices.uninitialize();
    }
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
void randar::Geometry::drawTo(Framebuffer &fb)
{
    this->sync();
    this->vertices.bind();
    this->indices.bind();

    fb.bind();
    ::glDrawElements(GL_TRIANGLES, this->indices.count(), GL_UNSIGNED_INT, 0);
}

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

// Appends the index of an available vertex to the geometry shape.
void randar::Geometry::appendIndex(unsigned int index)
{
    this->indices.append(index);
}

// Appends a vertex to the geometry shape.
void randar::Geometry::append(const randar::Vertex& vertex)
{
    this->appendIndex(this->useVertex(vertex));
}

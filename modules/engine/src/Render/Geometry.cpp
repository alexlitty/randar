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

void randar::Geometry::initialize()
{
    this->vertices.initialize();
    this->indices.initialize();
}

void randar::Geometry::uninitialize()
{
    if (this->isInitialized()) {
        this->vertices.uninitialize();
        this->indices.uninitialize();
    }
}

bool randar::Geometry::isInitialized()
{
    return this->ctx
        && this->vertices.isInitialized()
        && this->indices.isInitialized();
}

void randar::Geometry::appendVertex(const Vertex& vertex)
{
    this->vertices.append(vertex);
}

void randar::Geometry::appendIndex(unsigned int index)
{
    this->indices.append(index);
}

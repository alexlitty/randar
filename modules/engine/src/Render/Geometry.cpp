#include <randar/IO/Randar.hpp>
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

randar::Geometry randar::Geometry::copy()
{
    randar::Geometry geo;
    geo = *this;
    return geo;
}

// Destructor.
randar::Geometry::~Geometry()
{
    this->uninitialize();
}

// Identifiers the Randar object type.
std::string randar::Geometry::kind() const
{
    return "geometry";
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

// Appends another geometry to this geometry.
void randar::Geometry::append(randar::Geometry& other)
{
    this->append(other, randar::Transform::Identity);
}

void randar::Geometry::append(randar::Geometry& other, const randar::Transform& transform)
{
    for (uint32_t i = 0; i < other.indices.count(); i++) {
        randar::Vertex vertex = other.vertices.get(other.indices.get(i));
        vertex.position.transform(transform.transformMatrix());
        vertex.normal.transform(transform.transformMatrix());

        this->append(vertex);
    }
}

// Saves and loads the geometry from disk.
void randar::Geometry::save(const randar::Path& path)
{
    randar::exportGeometry(path, *this);
}

void randar::Geometry::load(const randar::Path& path)
{
    randar::importGeometry(path, *this);
}

// Node.js helper.
randar::Geometry randar::geometry()
{
    return randar::Geometry();
}

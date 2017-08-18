#include <randar/Render/Vertex.hpp>

// Constructors.
randar::Vertex::Vertex(const randar::Vector3& p, const Color& c)
: position(p),
  color(c)
{

}

randar::Vertex::Vertex(float x, float y, float z)
: randar::Vertex::Vertex(randar::Vector3(x, y, z))
{

}

randar::Vertex::Vertex(
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    float a)
: randar::Vertex::Vertex(randar::Vector3(x, y, z), randar::Color(r, g, b, a))
{

}

// Copy constructor and assignment operator.
randar::Vertex::Vertex(const randar::Vertex& other)
{
    *this = other;
}

randar::Vertex& randar::Vertex::operator =(const randar::Vertex& other)
{
    this->position          = other.position;
    this->color             = other.color;
    this->textureId         = other.textureId;
    this->textureCoordinate = other.textureCoordinate;
    this->jointWeights      = other.jointWeights;

    return *this;
}

// Appends this vertex to an ongoing array.
void randar::Vertex::appendTo(GLfloat* array) const
{
    array[0]  = position.x;
    array[1]  = position.y;
    array[2]  = position.z;
    array[3]  = color.r();
    array[4]  = color.g();
    array[5]  = color.b();
    array[6]  = color.a();

    // Joints.
    array[7]  = 0;
    array[8]  = 0;
    array[9]  = 0;
    array[10] = 0;

    // Joint weights.
    array[11] = 0;
    array[12] = 0;
    array[13] = 0;
    array[14] = 0;

    array[15] = textureCoordinate.u();
    array[16] = textureCoordinate.v();
}

// Returns the vertex with a slight modification.
randar::Vertex randar::Vertex::withPosition(const randar::Vector3& newPosition) const
{
    randar::Vertex vertex(*this);
    vertex.position = newPosition;
    return vertex;
}

randar::Vertex randar::Vertex::withPosition(float x, float y, float z) const
{
    return (*this).withPosition(randar::Vector3(x, y, z));
}

randar::Vertex randar::Vertex::withColor(const randar::Color& newColor) const
{
    randar::Vertex vertex(*this);
    vertex.color = newColor;
    return vertex;
}

randar::Vertex randar::Vertex::withNormal(const randar::Vector3& newNormal) const
{
    randar::Vertex vertex(*this);
    vertex.normal = newNormal;
    return vertex;
}

randar::Vertex randar::Vertex::withTextureId(int8_t newTextureId) const
{
    randar::Vertex vertex(*this);
    vertex.textureId = newTextureId;
    return vertex;
}

randar::Vertex randar::Vertex::withUV(const randar::Vector2<float>& newUv) const
{
    randar::Vertex vertex(*this);
    vertex.textureCoordinate = newUv;
    return vertex;
}

randar::Vertex randar::Vertex::withUV(float u, float v) const
{
    randar::Vertex vertex(*this);
    vertex.textureCoordinate.u(u);
    vertex.textureCoordinate.v(v);
    return vertex;
}

randar::Vertex randar::Vertex::withJoint(uint16_t jointIndex, uint8_t jointWeight) const
{
    randar::Vertex vertex(*this);
    vertex.jointWeights[jointIndex] = jointWeight;
    return vertex;
}

// Vertex comparison operator.
bool randar::operator ==(const randar::Vertex& a, const randar::Vertex& b)
{
    return a.position == b.position
        && a.color == b.color
        && a.textureId == b.textureId
        && a.textureCoordinate == b.textureCoordinate
        && a.jointWeights == b.jointWeights;
}

// Node.js helpers for intuitive vertex creation.
randar::Vertex randar::vertex(const randar::Vector3& p, const randar::Color& c)
{
    return randar::Vertex(p, c);
}

randar::Vertex randar::vertex(float x, float y, float z)
{
    return randar::Vertex(x, y, z);
}

randar::Vertex randar::vertex(
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    float a)
{
    return randar::Vertex(x, y, z, r, g, b, a);
}

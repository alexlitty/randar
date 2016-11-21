#include <randar/render/Vertex.hpp>

std::vector<randar::VertexAttribute> randar::Vertex::attributes = {
    VertexAttribute(0, 3, 3 * sizeof(GLfloat)),
    VertexAttribute(1, 4, 4 * sizeof(GLfloat))
};

unsigned int randar::Vertex::stride = 7;
unsigned int randar::Vertex::size = 7 * sizeof(GLfloat);

randar::Vertex::Vertex()
: randar::Vertex::Vertex(randar::Vector(), randar::Color())
{

}

randar::Vertex::Vertex(Vector initPosition, Color initColor)
: position(initPosition),
  color(initColor)
{

}

void randar::Vertex::appendTo(GLfloat* array) const
{
    array[0] = position.x;
    array[1] = position.y;
    array[2] = position.z;
    array[3] = color.r;
    array[4] = color.g;
    array[5] = color.b;
    array[6] = color.a;
}

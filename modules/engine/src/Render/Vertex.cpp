#include <randar/Render/Vertex.hpp>

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
    array[0]  = position.x;
    array[1]  = position.y;
    array[2]  = position.z;
    array[3]  = color.r;
    array[4]  = color.g;
    array[5]  = color.b;
    array[6]  = color.a;

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

    array[15] = textureCoordinate.u;
    array[16] = textureCoordinate.v;
}

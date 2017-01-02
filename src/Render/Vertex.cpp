#include <randar/Render/Vertex.hpp>

const unsigned int randar::Vertex::stride = 17;

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
    array[7]  = boneIndex[0];
    array[8]  = boneIndex[1];
    array[9]  = boneIndex[2];
    array[10] = boneIndex[3];
    array[11] = boneWeight[0];
    array[12] = boneWeight[1];
    array[13] = boneWeight[2];
    array[14] = boneWeight[3];
    array[15] = textureCoordinate.u;
    array[16] = textureCoordinate.v;
}

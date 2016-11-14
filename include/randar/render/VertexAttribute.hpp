#ifndef RANDAR_RENDER_VERTEX_ATTRIBUTE_HPP
#define RANDAR_RENDER_VERTEX_ATTRIBUTE_HPP

namespace randar
{
    struct VertexAttribute
    {
        unsigned int location;
        unsigned int size;
        unsigned int offset;

        VertexAttribute(unsigned int initLocation, unsigned int initSize, unsigned int initOffset);
    };
}

#endif

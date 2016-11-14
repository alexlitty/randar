#ifndef RANDAR_MATH_VECTOR_HPP
#define RANDAR_MATH_VECTOR_HPP

namespace randar
{
    struct Vector
    {
        float x;
        float y;
        float z;

        Vector();
        Vector(float xInit, float yInit, float zInit);
    };
}

#endif

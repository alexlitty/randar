#ifndef RANDAR_DATA_BYTE_HPP
#define RANDAR_DATA_BYTE_HPP

#include <randar/Data/Endian.hpp>

namespace randar
{
    typedef unsigned char Byte;

    template <typename T>
    inline Byte* asBytes(T& value)
    {
        return reinterpret_cast<Byte*>(&value);
    }

    inline float& asFloat(Byte* bytes)
    {
        return *reinterpret_cast<float*>(bytes);
    }
}

#endif

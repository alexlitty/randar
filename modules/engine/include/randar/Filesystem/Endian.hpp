#ifndef RANDAR_DATA_ENDIAN_HPP
#define RANDAR_DATA_ENDIAN_HPP

namespace randar
{
    /**
     * Swaps the endianness of a value.
     */
    template <typename T>
    void swapEndian(T& value)
    {
        char* swapped = new char[sizeof(value)];

        for (unsigned int i = 0; i < sizeof(value); i++) {
            swapped[sizeof(value) - 1 - i] = ((char*)(&value))[i];
        }

        for (unsigned int i = 0; i < sizeof(value); i++) {
            ((char*)(&value))[i] = swapped[i];
        }

        delete[] swapped;
    }

    /**
     * Normalizes a big endian value to little endian.
     */
    template <typename T>
    void normalizeBigEndian(T& value)
    {
        randar::swapEndian(value);
    }

    /**
     * Normalizes a little endian value.
     *
     * Since this platform is already little endian, does nothing.
     */
    template <typename T>
    void normalizeLittleEndian(T& value)
    {

    }
}

#endif

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

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
#define RANDAR_ENDIAN_BIG

// For now, we're not targeting any big endian platforms. Don't code for it yet.
#error "Randar does not support big endian platforms at this time."

    /**
     * Normalizes a big endian value.
     *
     * Since this platform is already big endian, does nothing.
     */
    template <typename T>
    void normalizeBigEndian(T& value)
    {

    }

    /**
     * Normalizes a little endian value to big endian.
     */
    template <typename T>
    void normalizeLittleEndian(T& value)
    {
        randar::swapEndian(value);
    }

#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
#define RANDAR_ENDIAN_LITTLE

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

#else
#error "Can't determine Endianness on this platform"
#endif

}

#endif

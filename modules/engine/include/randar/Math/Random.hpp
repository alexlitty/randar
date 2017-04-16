#ifndef RANDAR_MATH_RANDOM_HPP
#define RANDAR_MATH_RANDOM_HPP

#include <cstdlib>

namespace randar
{
    /**
     * Seeds the random number generator with the current time.
     */
    void seedRandomWithTime();

    /**
     * Generates a random float within [0, 1].
     */
    float randomFloat();

    /**
     * Generates a random float.
     */
    float randomFloat(float min, float max);

    /**
     * Generates a random integer.
     *
     * Random floats require different handling; Do not use floats for this
     * template typename. Use randomFloat instead.
     */
    template <typename T>
    T randomInt(T min, T max)
    {
        return std::rand() % (max - min + 1) + min;
    }
}

#ifdef SWIG
    %template(randomInt_int8) randar::randomInt<int8_t>;
    %template(randomInt_int16) randar::randomInt<int16_t>;
    %template(randomInt_int32) randar::randomInt<int32_t>;
    %template(randomInt_int64) randar::randomInt<int64_t>;

    %template(randomInt_uint8) randar::randomInt<uint8_t>;
    %template(randomInt_uint16) randar::randomInt<uint16_t>;
    %template(randomInt_uint32) randar::randomInt<uint32_t>;
    %template(randomInt_uint64) randar::randomInt<uint64_t>;
#endif

#endif

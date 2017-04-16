#ifndef RANDAR_UTILITY_CLAMP_HPP
#define RANDAR_UTILITY_CLAMP_HPP

namespace randar
{
    /**
     * Clamps a numeric value.
     */
    template <typename T>
    T clamp(T min, T max, T value)
    {
        if (value < min) {
            value = min;
        }

        else if (value > max) {
            value = max;
        }

        return value;
    }

    /**
     * Clamps a "signed" float within the standard [-1, 1].
     */
    float clampSignedFloat(float value);

    /**
     * Clamps an "unsigned" float within the standard [0, 1].
     */
    float clampUnsignedFloat(float value);
}

#ifdef SWIG
    %template(clamp_float) randar::clamp<float>;

    %template(clamp_int8) randar::clamp<int8_t>;
    %template(clamp_int16) randar::clamp<int16_t>;
    %template(clamp_int32) randar::clamp<int32_t>;
    %template(clamp_int64) randar::clamp<int64_t>;

    %template(clamp_uint8) randar::clamp<uint8_t>;
    %template(clamp_uint16) randar::clamp<uint16_t>;
    %template(clamp_uint32) randar::clamp<uint32_t>;
    %template(clamp_uint64) randar::clamp<uint64_t>;
#endif

#endif

#include <randar/Utility/Clamp.hpp>

// Clamps a "signed" float within the standard [-1, 1].
float randar::clampSignedFloat(float value)
{
    return randar::clamp<float>(-1.0f, 1.0f, value);
}

// Clamps an "unsigned" float within the standard [0, 1].
float randar::clampUnsignedFloat(float value)
{
    return randar::clamp<float>(0.0f, 1.0f, value);
}

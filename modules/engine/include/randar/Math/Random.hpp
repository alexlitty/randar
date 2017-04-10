#ifndef RANDAR_MATH_RANDOM_HPP
#define RANDAR_MATH_RANDOM_HPP

namespace randar
{
    void seedRandomWithTime();

    float random(float min, float max);
    int random(int min, int max);
}

#endif

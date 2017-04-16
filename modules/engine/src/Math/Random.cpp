#include <ctime>
#include <randar/Math/Random.hpp>

// Seeds the random number generator with the current time.
void randar::seedRandomWithTime()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
}

// Generates a random float within [0, 1].
float randar::randomFloat()
{
    return std::rand();
}

// Generates a random float.
float randar::randomFloat(float min, float max)
{
    return min + (std::rand() / (RAND_MAX / (max - min)));
}

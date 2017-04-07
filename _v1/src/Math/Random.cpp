#include <cstdlib>
#include <ctime>
#include <randar/Math/Random.hpp>

void randar::seedRandomWithTime()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
}

float randar::random(float min, float max)
{
    return min + (std::rand() / (RAND_MAX / (max - min)));
}

int randar::random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

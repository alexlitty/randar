#ifndef RANDAR_UTILITY_VECTOR_HPP
#define RANDAR_UTILITY_VECTOR_HPP

#include <vector>

namespace randar
{
    /**
     * Every time you call this, a puppy dies.
     *
     * @todo - Find a way to avoid this nonsense.
     */
    template <typename T>
    unsigned int getAvailableIndex(std::vector<T*> vector)
    {
        unsigned int size = vector.size();
        for (unsigned int i = 0; i < size; i++) {
            if (vector[i] == nullptr) {
                return i;
            }
        }
        return size;
    }
}

#endif

#ifndef RANDAR_UTILITY_MAP_HPP
#define RANDAR_UTILITY_MAP_HPP

#include <map>
#include <stdexcept>

namespace randar
{
    /**
     * Check if a key exists in a map.
     */
    template <typename T, typename U>
    bool hasKey(const std::map<T, U>& map, const T& key)
    {
        return map.find(key) != map.end();
    }

    /**
     * Assert the existence of a key in a map.
     *
     * If assertion fails, a runtime error is thrown.
     */
    template <typename T, typename U>
    void assertKey(const std::map<T, U>& map, const T& key)
    {
        if (!randar::hasKey(map, key)) {
            throw std::runtime_error("Map key missing");
        }
    }

    /**
     * Find the next available integer key in a map.
     *
     * @todo - Quite inefficient. Consider a different data structure for this
     * sort of thing.
     */
    template <typename T>
    unsigned int getAvailableKey(const std::map<unsigned int, T>& map)
    {
        unsigned int size = map.size();

        for (unsigned int i = 0; i < size; i++) {
            if (randar::hasKey(map, i)) {
                return i;
            }
        }
        return size;
    }
}

#endif

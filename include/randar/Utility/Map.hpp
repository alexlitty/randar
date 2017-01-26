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
     * Asserts the non-existence of a key in a map.
     *
     * If assertion fails, a runtime error is thrown.
     */
    template <typename T, typename U>
    void assertNoKey(const std::map<T, U>& map, const T& key)
    {
        if (randar::hasKey(map, key)) {
            throw std::runtime_error("Map key already exists");
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

    /**
     * Insert an item at the next available integer key in a map.
     *
     * Returns the key at which insertion occurred.
     */
    template <typename T>
    unsigned int insertAtAvailableKey(std::map<unsigned int, T>& map, const T& item)
    {
        unsigned int key = randar::getAvailableKey(map);
        map[key] = item;
        return key;
    }

    /**
     * Generates a unique key based on a desired key.
     *
     * Returns the final key chosen.
     */
    template <typename T>
    std::string generateUniqueKey(
        std::map<std::string, T>& map,
        const std::string& suggestedKey)
    {
        std::string key(suggestedKey);
        unsigned int suffix = 0;

        while (map.count(key)) {
            key = suggestedKey + "_" + std::to_string(suffix);
            suffix++;
        }

        return key;
    }

    /**
     * Inserts an item into a map with a unique key, based on a desired key.
     *
     * Returns the final key chosen.
     */
    template <typename T, typename U>
    std::string insertUniqueKey(
        std::map<std::string, T>& map,
        const std::string& suggestedKey,
        U& item)
    {
        std::string key = randar::generateUniqueKey(map, suggestedKey);

        map[key] = item;
        return key;
    }
}

#endif

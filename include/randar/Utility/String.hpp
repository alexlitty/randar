#ifndef RANDAR_UTILITY_STRING_HPP
#define RANDAR_UTILITY_STRING_HPP

#include <string>
#include <vector>

namespace randar
{
    /**
     * Whether a string is an integer.
     */
    bool isInteger(const std::string& str);

    /**
     * Converts a string to lowercase.
     */
    std::string toLowercase(const std::string& str);

    /**
     * Splits a string into a vector based on a delimiter.
     */
    void split(
        const std::string& str,
        char delimiter,
        std::vector<std::string>& results);

    std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * Joins a list of strings together using a delimiter.
     */
    std::string join(const std::vector<std::string>& parts, char delimiter);
}

#endif

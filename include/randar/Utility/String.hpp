#ifndef RANDAR_UTILITY_STRING_HPP
#define RANDAR_UTILITY_STRING_HPP

#include <string>

namespace randar
{
    /**
     * Converts a string to lowercase.
     */
    std::string toLowercase(const std::string& str);

    /**
     * Splits a string into a vector based on a delimiter.
     */
    void split(
        const std::string& str,
        const std::string& delimiter,
        std::vector<std::string>& results);

    std::vector<std::string> split(
        const std::string& str,
        const std::string& delimiter);

    /**
     * Joins a list of strings together using a delimiter.
     */
    std::string join(
        const std::vector<std::string>& parts,
        const std::string& delimiter);
}

#endif

#include <locale>
#include <sstream>
#include <randar/Utility/String.hpp>

// Converts a string to lowercase.
std::string randar::toLowercase(const std::string& str)
{
    static std::locale locale;
    std::string result;

    for (auto item : str) {
        result += std::tolower(item, locale);
    }

    return result;
}

// Splits a string into a vector based on a delimiter.
void randar::split(
    const std::string& str,
    const std::string& delimiter
    std::vector<std::string>& results)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        results.push_back(item);
    }
}

std::vector<std::string> randar::split(
    const std::string& str,
    const std::string& delimiter)
{
    std::vector<std::string> results;
    randar::split(str, delimiter, results);
    return results;
}

// Joins a list of strings together using a delimiter.
std::string randar::join(
    const std::vector<std::string>& parts,
    const std::string& delimiter)
{
    std::string result;

    uint32_t partCount = parts.size();
    for (uint32_t i = 0; i < partCount; i++) {
        result += parts[i];

        if ((i + 1) < partCount) {
            result += delimiter;
        }
    }

    return result;
}

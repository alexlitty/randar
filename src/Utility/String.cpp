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

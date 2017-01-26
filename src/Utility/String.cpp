#include <locale>
#include <randar/Utility/String.hpp>

std::string randar::toLowercase(const std::string& str)
{
    static std::locale locale;
    std::string result;

    for (auto item : str) {
        result += std::tolower(item, locale);
    }

    return result;
}

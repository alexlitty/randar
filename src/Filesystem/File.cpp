#include <regex>
#include <randar/Filesystem/File.hpp>
#include <randar/Utility/String.hpp>

// Retrieves the file extension.
std::string randar::File::getExtension() const
{
    std::smatch matches;

    std::regex regex(".+[.](.+)$");
    if (!std::regex_search(this->toString(), matches, regex) || matches.size() != 2) {
        return "";
    }

    return randar::toLowercase(matches[1]);
}

// Retrieves the file base name.
std::string randar::File::getBaseName() const
{
    std::smatch matches;

    std::regex regex(".*\\/(.+)[.].+$");
    if (!std::regex_search(this->toString(), matches, regex) || matches.size() != 2) {
        return "";
    }

    return matches[1];
}

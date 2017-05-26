#include <regex>
#include <randar/Filesystem/Directory.hpp>
#include <randar/Filesystem/File.hpp>
#include <randar/Utility/String.hpp>

// Retrieves the file extension.
std::string randar::File::extension() const
{
    std::smatch matches;

    std::regex regex(".+[.](.+)$");
    if (!std::regex_search((const std::string&)this->toString(), matches, regex) || matches.size() != 2) {
        return "";
    }

    return randar::toLowercase(matches[1]);
}

// Retrieves the file base name.
std::string randar::File::basename() const
{
    std::smatch matches;

    std::regex regex(".*\\/(.+)[.].+$");
    if (!std::regex_search((const std::string&)this->toString(), matches, regex) || matches.size() != 2) {
        return "";
    }

    return matches[1];
}

// Retrieves the directory containing this file.
randar::Directory randar::File::directory() const
{
    if (this->parts.size() == 0) {
        return randar::Directory("..");
    }

    if (this->parts.size() == 1) {
        return randar::Directory(".");
    }

    randar::File tmp(*this);
    tmp.parts.pop_back();
    return randar::Directory(tmp.toString());
}

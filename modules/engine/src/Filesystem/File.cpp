#include <regex>
#include <randar/Filesystem/Directory.hpp>
#include <randar/Filesystem/File.hpp>
#include <randar/Utility/String.hpp>

// Constructors.
randar::File::File()
: randar::Path()
{

}

randar::File::File(const std::string& path)
: randar::Path(path)
{

}

// Assignment.
randar::File::File(const randar::Path& path)
: randar::Path(path)
{

}

randar::File::File(const randar::File& other)
: randar::Path(other)
{

}

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
    return randar::Directory(this->parent());
}

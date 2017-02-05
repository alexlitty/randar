#include <regex>
#include <randar/Utility/File.hpp>
#include <randar/Utility/String.hpp>
#include <tinydir.h>

// Retrieves a file's extension.
std::string randar::getFileExtension(const std::string& file)
{
    std::smatch matches;

    std::regex regex(".+[.](.+)$");
    if (!std::regex_search(file, matches, regex) || matches.size() != 2) {
        return "";
    }

    return randar::toLowercase(matches[1]);
}

// Retrieves a file's base name.
std::string randar::getFileBaseName(const std::string& file)
{
    std::smatch matches;

    std::regex regex(".*\\/(.+)[.].+$");
    if (!std::regex_search(file, matches, regex) || matches.size() != 2) {
        return "";
    }

    return matches[1];
}

// Loads an ASCII file into memory.
std::string randar::readAsciiFile(std::string filename)
{
    std::ifstream stream(filename, std::ios::in);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot read ASCII file: " + filename);
    }

    std::string result;
    std::string line;
    while (std::getline(stream, line)) {
        result += line + "\n";
    }
    return result;
}

// Writes an ASCII file to disk.
bool randar::writeAsciiFile(std::string filename, std::string contents)
{
    std::ofstream stream(filename, std::ofstream::out);
    if (!stream.is_open()) {
        return false;
    }

    stream << contents;

    stream.close();
    return !stream.bad();
}

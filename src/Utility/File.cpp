#include <regex>
#include <randar/Utility/File.hpp>
#include <randar/Utility/String.hpp>

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

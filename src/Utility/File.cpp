#include <randar/Utility/File.hpp>

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

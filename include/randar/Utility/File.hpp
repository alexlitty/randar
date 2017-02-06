#ifndef RANDAR_UTILITY_FILE_HPP
#define RANDAR_UTILITY_FILE_HPP

#include <fstream>
#include <stdexcept>

namespace randar
{
    /**
     * Loads an ASCII file into memory.
     */
    std::string readAsciiFile(std::string filename);

    /**
     * Writes an ASCII file to disk.
     */
    bool writeAsciiFile(std::string filename, std::string contents);
}

#endif

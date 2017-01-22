#ifndef RANDAR_DATA_BINARY_FILE_INPUT_HPP
#define RANDAR_DATA_BINARY_FILE_INPUT_HPP

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <randar/Data/Endian.hpp>

namespace randar
{
    class BinaryFileInput
    {
        std::ifstream stream;

    public:
        /**
         * Constructor.
         */
        BinaryFileInput(const std::string& file)
        {
            this->stream.open(file, std::ios_base::in);
        }

        /**
         * Reads a variable type of data from the stream.
         */
        template <typename T>
        void read(T& value)
        {
            if (!this->stream.is_open()) {
                throw std::runtime_error("Reading from closed binary file");
            }
            this->stream.read(reinterpret_cast<char*>(&value), sizeof value);
        }

        template <typename T>
        T read()
        {
            T value;
            this->read(value);
            return value;
        }

        /**
         * Reads a null-terminated string from the stream.
         */
        void read(std::string& value)
        {
            value.clear();

            char character;
            while ((character = this->read<char>()) != '\0') {
                value += character;
            }
        }
    };
}

#endif

#ifndef RANDAR_DATA_BINARY_FILE_INPUT_HPP
#define RANDAR_DATA_BINARY_FILE_INPUT_HPP

#include <fstream>
#include <stdexcept>
#include <randar/Filesystem/Endian.hpp>

namespace randar
{
    class BinaryFileReader
    {
        std::ifstream stream;

    public:
        /**
         * Constructor.
         */
        BinaryFileReader(const std::string& file)
        {
            this->stream.open(file, std::ios::binary);
            if (!this->stream) {
                throw std::runtime_error("Cannot open binary file for reading");
            }
        }

        /**
         * Reads a variable type of data from the file.
         */
        template <typename T>
        void read(T* values, uint32_t count)
        {
            if (!this->stream) {
                throw std::runtime_error("Binary file input stream unexpectedly closed");
            }
            this->stream.read(reinterpret_cast<char*>(values), sizeof(values) * count);
        }

        template <typename T>
        void read(T& value)
        {
            if (!this->stream) {
                throw std::runtime_error("Binary file input stream unexpectedly closed");
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
         * Reads a null-terminated string from the file.
         */
        void read(std::string& value)
        {
            value.clear();

            char character;
            while ((character = this->read<char>()) != '\0') {
                value += character;
            }
        }

        /**
         * Closes the file from further reading.
         */
        void close()
        {
            this->stream.close();
        }
    };
}

#endif

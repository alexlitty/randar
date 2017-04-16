#ifndef RANDAR_DATA_BINARY_FILE_OUTPUT_HPP
#define RANDAR_DATA_BINARY_FILE_OUTPUT_HPP

#include <fstream>
#include <stdexcept>
#include <randar/Filesystem/Endian.hpp>
#include <randar/Render/Color.hpp>

namespace randar
{
    class BinaryFileWriter
    {
        std::ofstream stream;

    public:
        /**
         * Constructor.
         */
        BinaryFileWriter(const std::string& file)
        {
            this->stream.open(file, std::ios::binary);
        }

        /**
         * Writes a variable type of data to the file.
         */
        template <typename T>
        void write(const T& value)
        {
            this->stream.write(reinterpret_cast<const char*>(&value), sizeof value);
        }

        /**
         * Writes numeric values to the file.
         */
        void write(float value)
        {
            this->stream.write(reinterpret_cast<const char*>(&value), sizeof value);
        }

        /**
         * Writes a string to the file, with an appended null terminator.
         */
        void write(const std::string& value)
        {
            unsigned int length = value.size();
            for (unsigned int i = 0; i < length; i++) {
                this->write((char)value[i]);
            }
            this->write('\0');
        }

        /**
         * Closes the file from further writing.
         */
        void close()
        {
            this->stream.close();
        }
    };
}

#endif

#ifndef RANDAR_ENGINE_FILE_RESOURCE_HPP
#define RANDAR_ENGINE_FILE_RESOURCE_HPP

#include <string>

namespace randar
{
    /**
     * A resource which may be partially or completely stored in a file.
     */
    class FileResource
    {
        /**
         * Path to the file, relative to the root project directory.
         */
        std::string file;

        /**
         * Reads and processes file data for this resource.
         */
        virtual bool read() = 0;

        /**
         * Writes the file data for this resource.
         */
        virtual bool write() = 0;

    public:
        /**
         * Sets the file for this resource.
         */
        void setFile(const std::string& newFile);
    };
}

#endif

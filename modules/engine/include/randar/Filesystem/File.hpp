#ifndef RANDAR_FILESYSTEM_FILE_HPP
#define RANDAR_FILESYSTEM_FILE_HPP

#include <randar/Filesystem/Path.hpp>

namespace randar
{
    class Directory;

    class File : public Path
    {
    public:
        /**
         * Constructors.
         */
        File();
        File(const std::string& path);

        /**
         * Assignment.
         */
        File(const randar::Path& path);
        File(const randar::File& other);

        /**
         * Retrieves the file extension.
         *
         * Always returned in lowercase.
         */
        std::string extension() const;

        /**
         * Retrieves the file base name.
         *
         * The base name is the path of the file without directory and
         * extension.
         */
        std::string basename() const;

        /**
         * Retrieves the directory containing this file.
         */
        Directory directory() const;
    };
}

#endif

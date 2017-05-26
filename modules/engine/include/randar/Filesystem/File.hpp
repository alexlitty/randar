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
         * Inherit constructors.
         */
        using Path::Path;

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
    };
}

#endif

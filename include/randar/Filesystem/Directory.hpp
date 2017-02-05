#ifndef RANDAR_FILESYSTEM_DIRECTORY_HPP
#define RANDAR_FILESYSTEM_DIRECTORY_HPP

#include <randar/Filesystem/File.hpp>

namespace randar
{
    class Directory : public Path
    {
        /**
         * Inherit constructors.
         */
        using Path::Path;

        /**
         * Retrieves a list of files in this directory.
         */
        std::vector<File> getFiles() const;
    };
}

#endif

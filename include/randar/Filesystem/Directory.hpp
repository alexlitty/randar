#ifndef RANDAR_FILESYSTEM_DIRECTORY_HPP
#define RANDAR_FILESYSTEM_DIRECTORY_HPP

#include <randar/Filesystem/File.hpp>

namespace randar
{
    class Directory : virtual public Path
    {
    public:
        /**
         * Inherit constructors and operators.
         */
        using Path::Path;
        using Path::operator =;

        /**
         * Retrieves a subdirectory instance.
         */
        Directory getSubdirectory(const std::string& subdirectory) const;

        /**
         * Retrieves a list of files in this directory.
         */
        std::vector<File> getFiles() const;

        /**
         * Converts to a platform-appropriate string.
         */
        virtual std::string toString() const override;
    };
}

#endif

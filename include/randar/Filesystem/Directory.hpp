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
         * A static directory of temporary files.
         */
        static Directory Temp;

        /**
         * Retrieves a subdirectory instance.
         */
        Directory getSubdirectory(const std::string& subdirectory) const;

        /**
         * Retrieves a file in this directory.
         */
        File getFile(const std::string& filename) const;
        File getFile(
            const std::string& basename,
            const std::string& extension) const;

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

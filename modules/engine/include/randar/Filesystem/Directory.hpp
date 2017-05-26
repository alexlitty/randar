#ifndef RANDAR_FILESYSTEM_DIRECTORY_HPP
#define RANDAR_FILESYSTEM_DIRECTORY_HPP

#include <randar/Filesystem/File.hpp>

namespace randar
{
    class Directory : virtual public Path
    {
    public:
        /**
         * Constructors.
         */
        Directory();
        Directory(const std::string& path);

        /**
         * Assignment.
         */
        Directory(const randar::Path& path);
        Directory(const randar::Directory& other);

        /**
         * Creates the directory on the filesystem.
         *
         * Parent directories are also created if they do not exist.
         *
         * Nothing happens if the directory already exists. Throws an exception
         * if the directory could not be created.
         */
        void create();

        /**
         * Retrieves a subdirectory instance.
         */
        Directory subdirectory(const std::string& subdirectory) const;

        /**
         * Retrieves a file in this directory.
         */
        File file(const std::string& filename) const;
        File file(
            const std::string& basename,
            const std::string& extension) const;

        /**
         * Retrieves a list of files in this directory.
         */
        std::vector<File> files() const;

        /**
         * Current working directory.
         *
         * Throws an exception if it cannot be found.
         */
        static Directory current();

        /**
         * Default temporary directory.
         */
        static Directory Temp;
    };
}

#endif

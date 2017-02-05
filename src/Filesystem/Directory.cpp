#include <tinydir.h>
#include <randar/Filesystem/Directory.hpp>

// Retrieves a subdirectory instance.
randar::Directory randar::Directory::getSubdirectory(const std::string& subdirectory) const
{
    return Directory(this->toString() + subdirectory);
}

// Retrieves a list of files in this directory.
std::vector<randar::File> randar::Directory::getFiles() const
{
    std::vector<randar::File> results;

    ::tinydir_dir handle;
    ::tinydir_open(&handle, this->toString().c_str());

    while (handle.has_next) {
        ::tinydir_file file;
        ::tinydir_readfile(&handle, &file);

        if (!file.is_dir) {
            results.push_back(
                randar::File(std::string(file.name))
            );
        }

        ::tinydir_next(&handle);
    }

    ::tinydir_close(&handle);
    return results;
}

// Converts to a platform-appropriate string.
std::string randar::Directory::toString() const
{
    return randar::Path::toString() + "/";
}

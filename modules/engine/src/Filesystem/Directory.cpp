#include <randar/Filesystem/Directory.hpp>

// A static directory of temporary files.
// @todo - Make this portable.
randar::Directory randar::Directory::Temp("/tmp");

// Retrieves a subdirectory instance.
randar::Directory randar::Directory::getSubdirectory(const std::string& subdirectory) const
{
    return Directory(this->toString() + subdirectory);
}

// Retrieves a file in this directory.
randar::File randar::Directory::getFile(const std::string& filename) const
{
    return File(this->toString() + filename);
}

randar::File randar::Directory::getFile(
    const std::string& basename,
    const std::string& extension) const
{
    return this->getFile(basename + "." + extension);
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
                randar::File(this->toString() + std::string(file.name))
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

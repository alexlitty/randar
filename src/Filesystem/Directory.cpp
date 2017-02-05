#include <tinydir.h>
#include <randar/Filesystem/Directory.hpp>

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

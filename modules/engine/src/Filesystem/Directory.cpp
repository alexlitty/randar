#include <tinydir.h>
#include <randar/Filesystem/Directory.hpp>
#include <randar/System/Execute.hpp>

// Constructors.
randar::Directory::Directory()
: randar::Path()
{

}

randar::Directory::Directory(const std::string& path)
: randar::Path(path)
{

}

// Assignment.
randar::Directory::Directory(const randar::Path& path)
: randar::Path(path)
{

}

randar::Directory::Directory(const randar::Directory& other)
: randar::Path(other)
{

}

// Creates the directory on the filesystem.
void randar::Directory::create()
{
    if (randar::execute("mkdir -p " + this->toString()) != 0) {
        throw std::runtime_error(
            "Failed to create directory: " + this->toString()
        );
    }
}

// Retrieves a subdirectory instance.
randar::Directory randar::Directory::subdirectory(const std::string& subdirectory) const
{
    return this->child(subdirectory);
}

// Retrieves a file in this directory.
randar::File randar::Directory::file(const std::string& filename) const
{
    return this->child(filename);
}

randar::File randar::Directory::file(
    const std::string& basename,
    const std::string& extension) const
{
    return this->file(basename + "." + extension);
}

// Retrieves a list of files in this directory.
std::vector<randar::File> randar::Directory::files() const
{
    std::vector<randar::File> results;

    ::tinydir_dir handle;
    ::tinydir_open(&handle, this->toString().c_str());

    while (handle.has_next) {
        ::tinydir_file file;
        ::tinydir_readfile(&handle, &file);

        if (!file.is_dir) {
            results.push_back(this->file(file.name));
        }

        ::tinydir_next(&handle);
    }

    ::tinydir_close(&handle);
    return results;
}

// Current working directory.
randar::Directory randar::Directory::current()
{
    char buffer[randar::Path::max];

#if defined (__linux__)

    ssize_t count = ::readlink("/proc/self/exe", buffer, randar::Path::max);
    if (count < 0) {
        throw std::runtime_error("Failed to get current directory");
    }
    std::string path(buffer, count);

#elif defined (_WIN32)

    ::GetModuleFileName(NULL, buffer, randar::Path::max);
    std::string path(buffer);

#else
#error "Unimplemented randar::Directory::current"
#endif

    return randar::Directory(path);
}

// Default temporary directory.
randar::Directory randar::Directory::Temp("/tmp/randar");

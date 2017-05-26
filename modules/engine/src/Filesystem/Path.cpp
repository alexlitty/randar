#include <algorithm>
#include <randar/Filesystem/Path.hpp>

#if defined __linux__

#include <limits.h>
#include <unistd.h>

#elif defined _WIN32

#include <Windows.h>

#endif

// Default constructor.
randar::Path::Path()
: randar::Path(".")
{

}

// Constructor, given a UNIX-style string path.
randar::Path::Path(const std::string& path)
{
    *this = path;
}

// Copy constructor.
randar::Path::Path(const randar::Path& other)
: parts(other.parts)
{

}

// Destructor.
randar::Path::~Path()
{

}

// Converts to a platform-appropriate string.
std::string randar::Path::toString() const
{
    return randar::join(this->parts, '/');
}

// Assignment operator, to a UNIX-style string path.
randar::Path& randar::Path::operator =(const std::string& path)
{
    if (path == "") {
        this->parts.clear();
        this->parts.push_back(".");
    }

    else {
        randar::split(path, "/\\", this->parts);
    }

    return *this;
}

#if defined (__linux__)
std::string randar::Path::getCwd()
{
    char result[PATH_MAX];
    ssize_t count = ::readlink("/proc/self/exe", result, PATH_MAX);
    std::string programPath = std::string(result, (count > 0) ? count : 0);

    auto pos = programPath.find_last_of("/");
    return programPath.substr(0, pos + 1);
}
#elif defined (_WIN32)
std::string randar::Path::getCwd()
{
    char buffer[MAX_PATH];
    ::GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string path(buffer);
    auto pos = path.find_last_of("\\/");
    
    return path.substr(0, pos + 1);
}
#else
#error "Unimplemented randar::Path::getCwd()"
#endif

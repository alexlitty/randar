#include <randar/Filesystem/Path.hpp>

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

randar::Path& randar::Path::operator =(const randar::Path& other)
{
    this->parts = other.parts;
    return *this;
}

// Destructor.
randar::Path::~Path()
{

}

// Retrieves the path for the parent node.
randar::Path randar::Path::parent() const
{
    randar::Path path(*this);
    if (path.parts.size() == 0) {
        return path;
    }

    path.parts.pop_back();
    return path;
}

// Retrieves the path for a child node.
randar::Path randar::Path::child(const std::string& name) const
{
    randar::Path path(*this);
    path.parts.push_back(name);
    return path;
}

// Converts to a platform-appropriate string.
std::string randar::Path::toString() const
{
    if (this->parts.size() == 0) {
        return ".";
    }

    return randar::join(this->parts, '/');
}

// Maximum path size specified by the platform.
#if defined (__linux__)

    // PATH_MAX may be ridiculously large on Linux. We need to keep it within a
    // reasonable size since this value is used to construct char arrays.
    uint16_t randar::Path::max = std::min<uint16_t>(
        PATH_MAX, 4096
    );

#elif defined (_WIN32)

    uint16_t randar::Path::max = static_cast<uint16_t>(MAX_PATH);

#else
#error "Unimplemented randar::Path::max"
#endif

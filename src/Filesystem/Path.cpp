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

// Converts to a platform-appropriate string.
std::string randar::Path::toString() const
{
    return randar::join(this->parts, '/');
}

randar::Path::operator std::string() const
{
    return this->toString();
}

// Assignment operator.
randar::Path& randar::Path::operator =(const std::string& path)
{
    randar::split(path, '/', this->parts);
    return *this;
}

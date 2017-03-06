#include <randar/Filesystem/CefPath.hpp>

randar::CefPath::CefPath()
    : randar::Path()
{

}

randar::CefPath::CefPath(const std::string& path)
    : randar::Path(path)
{
    
}

randar::CefPath::CefPath(const CefPath& other)
    : randar::Path(other)
{

}

std::string randar::CefPath::toString() const
{
    return "file://" + randar::Path::toString();
}

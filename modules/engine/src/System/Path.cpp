#include <randar/System/Path.hpp>
#include <randar/Utility/String.hpp>

// Constructor.
randar::Path::Path(const std::string& path)
{
    this->set(path);
}

// Assignment.
randar::Path::Path(const randar::Path& other)
{
    *this = other;
}

randar::Path& randar::Path::operator =(const randar::Path& other)
{
    this->nodes = other.nodes;
    return *this;
}

// Sets the path using a string.
void randar::Path::set(const std::string& path)
{
    if (path.empty()) {
        this->nodes.clear();
        this->nodes.push_back(".");
        return;
    }

    randar::split(path, '/', this->nodes);

    // Remove trailing slashes.
    while (this->nodes.size() > 1 && this->nodes.back().empty()) {
        this->nodes.pop_back();
    }
}

// Gets the path to the parent node.
randar::Path randar::Path::parent() const
{
    if (!this->nodes.size()) {
        throw std::runtime_error("Corrupt path");
    }

    if (this->nodes.back() == ".." || this->nodes.back() == "~") {
        return this->child("..");
    }

    if (this->nodes.size() == 1) {
        if (this->nodes[0].empty()) {
            throw std::runtime_error("Root path has no parent");
        }
        
        if (this->nodes[0] == ".") {
            return randar::Path("..");
        }

        return randar::Path(".");
    }

    randar::Path result = *this;
    result.nodes.pop_back();
    return result;
}

// Gets the path to a child node.
randar::Path randar::Path::child(const std::string& node) const
{
    randar::Path result = *this;
    result.nodes.push_back(node);
    return result;
}

// Converts the path to a string.
std::string randar::Path::toString() const
{
    if (this->nodes.size() == 1 && this->nodes[0].empty()) {
        return "/";
    }

    return randar::join(this->nodes, '/');
}

// Node.js helper for intuitive path creation.
randar::Path randar::path(const std::string& str)
{
    return randar::Path(str);
}

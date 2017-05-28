#include <randar/System/Directory.hpp>
#include <randar/System/Execute.hpp>
#include <randar/Utility/String.hpp>

// Creates a directory.
void randar::createDirectory(randar::Path directory)
{
    if (!randar::execute("mkdir -p " + directory.toString())) {
        throw std::runtime_error(
            "Failed to create directory: " + directory.toString()
        );
    }
}

// Removes a directory.
void randar::removeDirectory(randar::Path directory)
{
    if (!randar::execute("rmdir -R " + directory.toString())) {
        throw std::runtime_error(
            "Failed to remove directory: " + directory.toString()
        );
    }
}

// Creates and returns a dedicated temporary directory.
randar::Path randar::tempDirectory()
{
    static std::string tempBase = "/tmp/randar";

    std::string output;
    if (!randar::execute("mktemp -d -p " + tempBase, output)) {
        std::string msg = "Failed to create temporary directory";
        if (!output.empty()) {
            msg += randar::trim(output);
        }

        throw std::runtime_error(msg);
    }

    return randar::Path(randar::trim(output));
}

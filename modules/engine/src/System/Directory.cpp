#include <randar/System/Directory.hpp>
#include <randar/System/Execute.hpp>
#include <randar/Utility/String.hpp>

// Creates a directory.
void randar::createDirectory(randar::Path directory)
{
    if (randar::execute("mkdir -p " + directory.toString())) {
        throw std::runtime_error(
            "Failed to create directory: " + directory.toString()
        );
    }
}

// Removes a directory.
void randar::removeDirectory(randar::Path directory)
{
    if (randar::execute("rm -R " + directory.toString())) {
        throw std::runtime_error(
            "Failed to remove directory: " + directory.toString()
        );
    }
}

// Returns the platform-specific temporary directory.
randar::Path randar::platformTempDirectory()
{
    return randar::Path("/tmp");
}

// Creates and returns a global temporary directory.
randar::Path randar::globalTempDirectory()
{
    randar::Path dir = randar::platformTempDirectory().child("randar");
    randar::createDirectory(dir);
    return dir;
}

// Creates and returns a dedicated temporary directory.
randar::Path randar::tempDirectory()
{
    std::string command = "mktemp -d -p "
                        + randar::globalTempDirectory().toString();

    std::string output;
    if (randar::execute(command, output)) {
        std::string msg = "Failed to create temporary directory";
        if (!output.empty()) {
            msg += ": " + randar::trim(output);
        }
        throw std::runtime_error(msg);
    }

    return randar::Path(randar::trim(output));
}

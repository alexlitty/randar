#ifndef RANDAR_SYSTEM_DIRECTORY_HPP
#define RANDAR_SYSTEM_DIRECTORY_HPP

#include <randar/System/Path.hpp>

namespace randar
{
    /**
     * Creates a directory.
     *
     * Nothing happens if the directory already exists. Parent directories
     * will also be created if they do not exist.
     */
    void createDirectory(randar::Path directory);

    /**
     * Removes a directory.
     *
     * Throws an exception if the directory could not be removed.
     */
    void removeDirectory(randar::Path directory);

    /**
     * Creates a returns a dedicated temporary directory.
     */
    randar::Path tempDirectory();
}

#endif

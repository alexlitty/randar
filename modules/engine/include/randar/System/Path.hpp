#ifndef RANDAR_SYSTEM_PATH_HPP
#define RANDAR_SYSTEM_PATH_HPP

#include <stdexcept>
#include <string>
#include <vector>

namespace randar
{
    struct Path
    {
        /**
         * Nodes in this path.
         *
         * Each node represents a filesystem entity -- a directory or file.
         */
        std::vector<std::string> nodes;

        /**
         * Constructor.
         */
        Path(const std::string& path = "");

        /**
         * Assignment.
         */
        Path(const Path& other);
        Path& operator =(const Path& other);

        /**
         * Sets the path using a string.
         */
        void set(const std::string& path);

        /**
         * Gets the path to the parent node.
         */
        Path parent() const;

        /**
         * Gets the path to a child node.
         */
        Path child(const std::string& node) const;

        /**
         * Converts the path to a string.
         */
        std::string toString() const;
    };

    /**
     * Node.js helper for intuitive path creation.
     */
    randar::Path path(const std::string& str = "");
}

#endif

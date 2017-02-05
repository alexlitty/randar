#ifndef RANDAR_FILESYSTEM_PATH_HPP
#define RANDAR_FILESYSTEM_PATH_HPP

#include <randar/Utility/String.hpp>

namespace randar
{
    class Path
    {
        std::vector<std::string> parts;

    public:
        /**
         * Default constructor.
         *
         * Set to the current working directory.
         */
        Path();

        /**
         * Constructor, given a UNIX-style string path.
         */
        Path(const std::string& path);

        /**
         * Converts to a platform-appropriate string.
         */
        std::string toString() const;
        operator std::string() const;

        /**
         * Assignment operator.
         */
        Path& operator =(const std::string& path);
    };
}

#endif

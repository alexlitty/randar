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
         * Copy constructor.
         */
        Path(const Path& other);

        /**
         * Converts to a platform-appropriate string.
         */
        virtual std::string toString() const;
        operator std::string() const;

        /**
         * Assignment operator, to a UNIX-style string path.
         */
        Path& operator =(const std::string& path);
    };
}

#endif

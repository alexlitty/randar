#ifndef RANDAR_FILESYSTEM_PATH_HPP
#define RANDAR_FILESYSTEM_PATH_HPP

#if defined __linux__
#include <limits.h>
#include <unistd.h>

#elif defined _WIN32
#include <Window.h>
#endif

#include <randar/Utility/String.hpp>

namespace randar
{
    class Path
    {
    protected:
        std::vector<std::string> parts;

    public:
        /**
         * Default constructor.
         *
         * Set to the current working directory.
         */
        Path();

        /**
         * Constructor, given a string path.
         * All platform paths supported
         */
        Path(const std::string& path);

        /**
         * Assignment.
         */
        Path(const Path& other);
        Path& operator =(const Path& other);

        /**
         * Destructor.
         */
        virtual ~Path();

        /**
         * Retrieves the path for the parent node.
         */
        Path parent() const;

        /**
         * Retrieves the path for a child node.
         */
        Path child(const std::string& name) const;

        /**
         * Converts to a platform-appropriate string.
         */
        virtual std::string toString() const;

        /**
         * Maximum path size specified by the platform.
         */
        static uint16_t max;
    };
}

#endif

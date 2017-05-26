#ifndef RANDAR_FILESYSTEM_PATH_HPP
#define RANDAR_FILESYSTEM_PATH_HPP

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
         * Copy constructor.
         */
        Path(const Path& other);

        /**
         * Destructor.
         */
        virtual ~Path();

        /**
         * Converts to a platform-appropriate string.
         */
        virtual std::string toString() const;
        operator std::string() const;

        /**
         * Assignment operator, to a string path.
         * All platform paths supported
         */
        Path& operator =(const std::string& path);

        /**
         * Returns Current Working Directory without the trailing slash.
         * Path delimiter will be platform specific.
         */
        static std::string getCwd();
    };
}

#endif

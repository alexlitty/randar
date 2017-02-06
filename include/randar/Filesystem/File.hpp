#ifndef RANDAR_FILESYSTEM_FILE_HPP
#define RANDAR_FILESYSTEM_FILE_HPP

#include <randar/Filesystem/Path.hpp>
#include <randar/Filesystem/BinaryFileStream.hpp>

namespace randar
{
    class File : public Path
    {
    public:
        /**
         * Inherit constructors.
         */
        using Path::Path;

        /**
         * Creates a new binary reading stream from this file.
         */
        BinaryFileReader createBinaryReader() const;

        /**
         * Creates a new binary writing stream to this file.
         */
        BinaryFileWriter createBinaryWriter() const;
    };
}

#endif

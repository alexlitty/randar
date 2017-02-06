#include <randar/Filesystem/File.hpp>

// Creates a new binary reading stream from this file.
randar::BinaryFileReader randar::File::createBinaryReader() const
{
    return BinaryFileReader(this->toString());
}

// Creates a new binary writing stream to this file.
randar::BinaryFileWriter randar::File::createBinaryWriter() const
{
    return BinaryFileWriter(this->toString());
}

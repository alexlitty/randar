#ifndef RANDAR_PROJECT_EXPORTER_HPP
#define RANDAR_PROJECT_EXPORTER_HPP

#include <randar/Filesystem/File.hpp>
#include <randar/Filesystem/BinaryFileStream.hpp>
#include <randar/Render/Texture.hpp>

namespace randar
{
    struct Exporter
    {
        static void exportRaTexture(const Texture& texture, const File& file);
    };
}

#endif

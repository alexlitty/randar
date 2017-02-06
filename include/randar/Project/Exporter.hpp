#ifndef RANDAR_PROJECT_EXPORTER_HPP
#define RANDAR_PROJECT_EXPORTER_HPP

#include <randar/Filesystem/File.hpp>
#include <randar/Render/Texture.hpp>

namespace randar
{
    struct Exporter
    {
        static void exportRaTexture(const Texture& texture, const File& file);
        static void exportRaModel(const Model& model, const File& file);
    };
}

#endif

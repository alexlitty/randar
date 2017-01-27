#ifndef RANDAR_PROJECT_IMPORTER_HPP
#define RANDAR_PROJECT_IMPORTER_HPP

#include <randar/Render/Model.hpp>

namespace randar
{
    struct Importer
    {
        std::map<std::string, Model*> models;
        std::map<std::string, Texture*> textures;

        ~Importer();
        void clear();

        void importIqm(const std::string& file);
        void importPng(const std::string& file);
    };
}

#endif

#ifndef RANDAR_PROJECT_IMPORTER_HPP
#define RANDAR_PROJECT_IMPORTER_HPP

#include <randar/Engine/Gpu.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Thread/Lockable.hpp>

namespace randar
{
    struct Importer : public Lockable
    {
        Gpu& gpu = randar::getDefaultGpu();

        std::map<std::string, Model*> models;
        std::map<std::string, Texture*> textures;

        ~Importer();
        bool isEmpty();
        void clear();

        void importIqm(const std::string& file);
        void importPng(const std::string& file);
    };
}

#endif

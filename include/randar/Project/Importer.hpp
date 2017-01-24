#ifndef RANDAR_PROJECT_IMPORTER_HPP
#define RANDAR_PROJECT_IMPORTER_HPP

#include <randar/Render/Model.hpp>

namespace randar
{
    struct Importer
    {
        std::map<std::string, Model*> models;

        ~Importer();
        void clear();

        void importIqm(const std::string& file);
    };
}

#endif

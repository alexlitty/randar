#ifndef RANDAR_PROJECT_IMPORTER_HPP
#define RANDAR_PROJECT_IMPORTER_HPP

#include <vector>
#include <randar/Render/Model.hpp>

namespace randar
{
    struct Importer
    {
        std::vector<Model*> models;

        ~Importer();
        void clear();

        void importIqm(const std::string& file);
    };
}

#endif

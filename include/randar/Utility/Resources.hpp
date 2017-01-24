#ifndef RANDAR_UTILITY_RESOURCES_HPP
#define RANDAR_UTILITY_RESOURCES_HPP

#include <fstream>
#include <sstream>
#include <map>
#include <randar/Render/Model.hpp>
#include <randar/Render/Material.hpp>
#include <randar/Physics/System.hpp>

namespace randar
{
    struct Resources
    {
        std::map<std::string, Material*> materials;
        std::map<std::string, Model*> models;
        std::map<std::string, System*> systems;

        ~Resources();

        void import(std::string filename);
        void importMtl(std::ifstream& file);
        void importIqm(std::ifstream& file);
    };
}

#endif

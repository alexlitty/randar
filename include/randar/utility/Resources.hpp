#ifndef RANDAR_UTILITY_RESOURCES_HPP
#define RANDAR_UTILITY_RESOURCES_HPP

#include <fstream>
#include <sstream>
#include <map>
#include <randar/render/Model.hpp>
#include <randar/physics/System.hpp>

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

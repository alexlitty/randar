#ifndef RANDAR_UTILITY_RESOURCES_HPP
#define RANDAR_UTILITY_RESOURCES_HPP

#include <fstream>
#include <sstream>
#include <map>
#include <randar/render/Model.hpp>

namespace randar
{
    struct Resources
    {
        std::map<std::string, Material*> materials;
        std::map<std::string, Model*> models;

        ~Resources();

        void import(std::string filename);
        void importMtl(std::ifstream& file);
        void importObj(std::string name, std::ifstream& file);
    };
}

#endif

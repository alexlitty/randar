#include <randar/Project/Importer.hpp>

randar::Importer::~Importer()
{
    for (auto model : this->models) {
        delete model.second;
    }

    for (auto texture : this->textures) {
        delete texture.second;
    }
}

void randar::Importer::clear()
{
    this->models.clear();
    this->textures.clear();
}

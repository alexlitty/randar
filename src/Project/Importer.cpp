#include <randar/Project/Importer.hpp>

randar::Importer::~Importer()
{
    for (auto model : this->models) {
        delete model.second;
    }

    this->clear();
}

void randar::Importer::clear()
{
    this->models.clear();
}

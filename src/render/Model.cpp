#include <randar/render/Model.hpp>

randar::Model::~Model()
{
    for (auto joint : this->joints) {
        delete joint;
    }
}

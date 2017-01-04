#include <randar/Render/Model.hpp>

randar::Model::Model()
{

}

randar::Model::~Model()
{
    for (auto joint : this->joints) {
        delete joint;
    }
}

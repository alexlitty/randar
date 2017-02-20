#include <randar/Scene/Scene.hpp>

// Destructor.
randar::Scene::~Scene()
{
    for (auto item : this->models) {
        delete item.second;
    }
}

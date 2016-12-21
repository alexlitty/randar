#include <randar/Scene.hpp>

randar::Scene::~Scene()
{

}

void randar::Scene::render()
{
    this->bind();
    this->clear(this->backgroundColor);
    this->draw(*this);
}

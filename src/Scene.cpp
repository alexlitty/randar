#include <randar/Scene.hpp>

randar::Scene::~Scene()
{

}

void randar::Scene::draw(randar::Vertices &vertices) const
{
    vertices.draw();
}

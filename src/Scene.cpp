#include <randar/Scene.hpp>

randar::Scene::~Scene()
{

}

void randar::Scene::clear(randar::Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void randar::Scene::draw(const randar::Vertices &vertices, randar::RenderState state) const
{
    state.camera = this->camera;
    vertices.draw(state);
}

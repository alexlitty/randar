#include <randar/Scene.hpp>

randar::Scene::~Scene()
{

}

void randar::Scene::draw(randar::Vertices &vertices, randar::RenderState state) const
{
    if (!state.shaderProgram) {
        throw std::runtime_error("Cannot draw without a shader program");
    }

    ::glUseProgram(*state.shaderProgram);
    vertices.draw();
}

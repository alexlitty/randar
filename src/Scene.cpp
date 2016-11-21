#include <randar/Scene.hpp>

randar::Scene::~Scene()
{

}

void randar::Scene::clear(randar::Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void randar::Scene::draw(randar::Vertices &vertices, randar::RenderState state) const
{
    if (!state.shaderProgram) {
        throw std::runtime_error("Cannot draw without a shader program");
    }

    ::glUseProgram(*state.shaderProgram);
    vertices.draw();
}

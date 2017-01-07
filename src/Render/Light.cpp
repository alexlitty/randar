#include <randar/Render/Light.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Light::Light()
: vertexShader(GL_VERTEX_SHADER, randar::readAsciiFile("./shaders/shadow.vert")),
  fragmentShader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./shaders/shadow.frag")),
  shaderProgram(this->vertexShader, this->fragmentShader)
{

}

void randar::Light::initialize()
{
    this->gpu.initialize(this->shaderProgram);
}

void randar::Light::destroy()
{
    this->gpu.destroy(this->shaderProgram);
}

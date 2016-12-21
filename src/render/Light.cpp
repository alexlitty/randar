#include <randar/render/Light.hpp>

randar::Light::Light()
{
    this->shadowVertexShader.load("./shaders/shadow.vert", GL_VERTEX_SHADER);
    this->shadowFragmentShader.load("./shaders/shadow.frag", GL_FRAGMENT_SHADER);
    this->shadowProgram.load(this->shadowVertexShader, this->shadowFragmentShader);
    this->renderTexture.shaderProgram = &this->shadowProgram;
}

void randar::Light::bind() const
{
    this->renderTexture.bind();
}

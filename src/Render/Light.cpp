#include <randar/Render/Light.hpp>

randar::Light::Light()
{
    this->requireShaderProgram(
        this->requireShader(
            randar::readAsciiFile("./shaders/shadow.vert"),
            GL_VERTEX_SHADER
        ),
        this->requireShader(
            randar::readAsciiFile("./shaders/shadow.frag"),
            GL_FRAGMENT_SHADER
        )
    );

    //this->renderTexture.useShaderProgram("shadow");
}

void randar::Light::bind() const
{
    this->renderTexture.bind();
}

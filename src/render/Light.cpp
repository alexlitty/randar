#include <randar/render/Light.hpp>

randar::Light::Light()
{
    this->requireShaderProgram(
        "shadow",
        this->requireShader(
            "shadow.vert",
            randar::readAsciiFile("./shaders/shadow.vert"),
            GL_VERTEX_SHADER
        ),
        this->requireShader(
            "shadow.frag",
            randar::readAsciiFile("./shaders/shadow.frag"),
            GL_FRAGMENT_SHADER
        )
    );

    this->renderTexture.useShaderProgram("shadow");
}

void randar::Light::bind() const
{
    this->renderTexture.bind();
}

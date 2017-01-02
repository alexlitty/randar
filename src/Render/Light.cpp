#include <randar/Render/Light.hpp>

randar::Light::Light()
{
    this->attach(
        new ShaderProgram(
            *new Shader(
                GL_VERTEX_SHADER,
                randar::readAsciiFile("./shaders/shadow.vert")
            ),

            *new Shader(
                GL_FRAGMENT_SHADER,
                randar::readAsciiFile("./shaders/shadow.frag")
            )
        )
    );

    //this->renderTexture.useShaderProgram("shadow");
}

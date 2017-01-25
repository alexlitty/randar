#include <randar/Resource/DefaultShaderProgram.hpp>

randar::Shader& randar::getDefaultVertexShader()
{
    static Shader defaultVertexShader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/default.vert"));
    return defaultVertexShader;
}

randar::Shader& randar::getDefaultFragmentShader()
{
    static Shader defaultFragmentShader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/default.frag"));
    return defaultFragmentShader;
}

randar::ShaderProgram& randar::getDefaultShaderProgram()
{
    static randar::ShaderProgram defaultShaderProgram(
        randar::getDefaultVertexShader(),
        randar::getDefaultFragmentShader()
    );

    return defaultShaderProgram;
}

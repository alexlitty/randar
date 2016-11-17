#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <fstream>
#include <stdexcept>
#include <string>
#include <GL/glew.h>

namespace randar
{
    class Shader
    {
        GLenum type;
        GLuint id;

    public:
        Shader(std::string file, GLenum initType);
        ~Shader();

        operator GLuint() const;
    };
}

#endif

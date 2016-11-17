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
        /**
         * Default constructor.
         *
         * Provided for convenience. Must be loaded before use.
         */
        Shader();

        /**
         * Constructs a shader from a file.
         */
        Shader(std::string file, GLenum initType);

        /**
         * Destructor.
         */
        ~Shader();

        /**
         * Loads and compiles a shader from a file.
         */
        void load(std::string file, GLenum initType);

        /**
         * Convert to the underlying OpenGL name.
         */
        operator GLuint() const;
    };
}

#endif

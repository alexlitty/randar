#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/render/Shader.hpp>

namespace randar
{
    class ShaderProgram
    {
        GLuint id;

    public:
        /**
         * Default constructor.
         *
         * Provided for convenience. Must be loaded before use.
         */
        ShaderProgram();

        /**
         * Construct from existing shaders.
         */
        ShaderProgram(Shader &vertexShader, Shader &fragmentShader);

        /**
         * Destructor.
         */
        ~ShaderProgram();

        /**
         * Links shaders together into a program.
         */
        void load(Shader &vertexShader, Shader &fragmentShader);

        /**
         * Convert to underlying OpenGL name.
         */
        operator GLuint() const;
    };
}

#endif

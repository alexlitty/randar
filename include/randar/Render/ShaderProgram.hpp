#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/Render/Shader.hpp>

namespace randar
{
    struct ShaderProgram : virtual public GpuResource
    {
        Shader vertexShader;
        Shader fragmentShader;

        /**
         * Constructs a new shader program.
         */
        ShaderProgram();

        /**
         * Constructs a new shader program as a copy of an existing one.
         *
         * If the existing program is initialized, this program will also be
         * initialized.
         */
        ShaderProgram(const ShaderProgram& other);

        /**
         * Constructs a shader program from existing shaders.
         */
        ShaderProgram(
            Shader& initVertexShader,
            Shader& initFragmentShader);

        /**
         * Destructor.
         */
        ~ShaderProgram();

        /**
         * Sets the program shaders and initializes the program.
         *
         * If the program was already initialized, it it destroyed first.
         */
        void set(
            const Shader& initVertexShader,
            const Shader& initFragmentShader);
    };
}

#endif

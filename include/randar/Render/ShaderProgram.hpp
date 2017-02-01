#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/Render/Shader.hpp>
#include <randar/Render/Uniform.hpp>

namespace randar
{
    class ShaderProgram : virtual public GpuResource
    {
    public:
        Shader vertexShader;
        Shader fragmentShader;

        /**
         * The uniforms required by this program.
         */
        mutable std::map<std::string, Uniform> uniforms;

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

    public:
        /**
         * Sets the program shaders and initializes the program.
         *
         * If the program was already initialized, it it destroyed first.
         */
        void set(
            const Shader& initVertexShader,
            const Shader& initFragmentShader);

        /**
         * Writes a value to a uniform.
         */
    };
}

#endif

#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/Render/Shader.hpp>
#include <randar/Utility/glm.hpp>

namespace randar
{
    class ShaderProgram : virtual public GpuResource
    {
        /**
         * The uniforms used by this program mapped against their locations.
         *
         * If a location is -1, the uniform has been requested somewhere but is
         * not used by the program.
         */
        std::map<std::string, ::GLint> uniformLocations;

    public:
        Shader vertexShader;
        Shader fragmentShader;

        /**
         * Constructs a new shader program.
         */
        ShaderProgram(Gpu* gpuInit = nullptr);

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

    protected:
        /**
         * Checks if a uniform is used by the program.
         */
        bool hasUniform(const std::string& name);

    public:
        /**
         * Sets the value of a uniform.
         *
         * Nothing happens if the uniform is not used by this program.
         */
        void setUniform(const std::string& name, const glm::mat4& matrix);
        void setUniform(const std::string& name, int integer);

        /**
         * Assignment operator.
         */
        ShaderProgram& operator =(const ShaderProgram& other);

        /**
         * Allow the GPU class to set uniform locations.
         */
        friend class Gpu;
    };
}

#endif

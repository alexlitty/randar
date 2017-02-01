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
         */
        std::map<std::string, ::GLint> uniformLocations;

        /**
         * Sets the location of a uniform.
         *
         * Nothing happens if the provided location is less than 0.
         *
         * Called by the GPU class during initialization.
         */
        void setUniformLocation(const std::string& name, ::GLint location);

    public:
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

        /**
         * Checks if this program uses a uniform.
         */
        bool hasUniform(const std::string& name) const;

        /**
         * Writes a value to a uniform.
         *
         * Nothing happens if the uniform is not used by this program.
         */
        void setUniform(const std::string& name, const glm::mat4& matrix);

        /**
         * Allow the GPU class to set uniform locations.
         */
        friend class Gpu;
    };
}

#endif

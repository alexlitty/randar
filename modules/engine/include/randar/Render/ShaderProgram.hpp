#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <map>
#include <randar/Render/Shader.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/System/GraphicsContextResource.hpp>
#include <randar/System/GlNamedResource.hpp>
#include <randar/Utility/glm.hpp>

namespace randar
{
    class ShaderProgram
    : virtual public GraphicsContextResource,
      virtual public GlNamedResource
    {
        /**
         * Shaders used by this program.
         */
        std::map<ShaderType, Shader*> shaders;

        /**
         * Uniforms used by this program mapped against their locations.
         *
         * If a location is -1, the uniform has been requested somewhere but is
         * not used by the program.
         */
        std::map<std::string, ::GLint> uniformLocations;

        /**
         * Whether the program needs to be re-initialized.
         */
        bool inSync = false;

    public:
        /**
         * Disable assignment.
         */
        ShaderProgram(const ShaderProgram& other) = delete;
        ShaderProgram& operator =(const ShaderProgram& other) = delete;

        /**
         * Constructor.
         */
        ShaderProgram(GraphicsContext& context);

        /**
         * Destructor.
         */
        ~ShaderProgram();

        /**
         * Whether this program is complete and linkable.
         */
        bool isComplete() const;

        /**
         * Initializes the program.
         *
         * Re-initializes the program if it is already initialized.
         *
         * Throws an exception if the program could not be initialized.
         */
        void initialize();

        /**
         * Uninitializes the program.
         *
         * Nothing happens if the program is not initialized.
         */
        void uninitialize();

        /**
         * Whether the program is initialized.
         */
        bool isInitialized() const;

        /**
         * Uses this program for further operations.
         */
        void use();

        /**
         * Attaches a shader to the program.
         *
         * If a shader of the same type is already being used, it is overridden.
         *
         * The shader must not be destroyed while the program exists.
         */
        void attach(Shader& shader);

        /**
         * Checks if a uniform is used by the program.
         */
        bool hasUniform(const std::string& name);

        /**
         * Sets the value of a uniform.
         *
         * Nothing happens if the uniform is not used by this program.
         */
        void uniform(const std::string& name, const glm::mat4& matrix);
        void uniform(const std::string& name, int integer);
        void uniform(const std::string& name, randar::Texture& texture);
    };
}

#endif

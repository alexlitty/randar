#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <randar/System/GraphicsContextResource.hpp>
#include <randar/System/GlNamedResource.hpp>

namespace randar
{
    class Shader
    : virtual public GraphicsContextResource,
      virtual public GlNamedResource
    {
    public:
        /**
         * Available shader types.
         */
        enum class Type {
            Vertex,
            Fragment
        };

    protected:
        Shader::Type shaderType = Shader::Type::Vertex;
        std::string shaderCode;

    public:
        /**
         * Disable assignment.
         */
        Shader(const Shader& other) = delete;
        Shader& operator =(const Shader& other) = delete;

        /**
         * Default constructor.
         */
        Shader();

        /**
         * Primary constructor.
         */
        Shader(GraphicsContext& context);

        /**
         * Destructor.
         */
        ~Shader();

        /**
         * Sets the context to initialize the shader with.
         *
         * Uninitializes the shader.
         */
        void context(GraphicsContext& newContext);

        /**
         * Initializes the shader.
         *
         * Re-initializes if the shader is already initialized.
         *
         * Throws an exception if the shader could not be initialized.
         */
        void initialize();
        void initialize(Shader::Type newType, const std::string& newCode);
        void initialize(std::string newType, const std::string& newCode);

        /**
         * Uninitializes the shader.
         *
         * Nothing happens if the shader is not initialized.
         */
        void uninitialize();

        /**
         * Whether the shader is initialized.
         */
        bool isInitialized() const;

        /**
         * Retrieves the Randar shader type.
         */
        Shader::Type type() const;

        /**
         * Retrieves the OpenGL shader type.
         */
        GLenum glType() const;

        /**
         * Generates the code for a default shader.
         */
        static std::string defaultCode(Shader::Type type);
    };
}

#endif

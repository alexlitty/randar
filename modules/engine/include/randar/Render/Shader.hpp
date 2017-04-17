#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Shader : virtual public GpuResource
    {
        GLenum shaderType;
        std::string code;

        /**
         * Constructs a new uninitialized shader.
         */
        Shader(Gpu* initGpu = nullptr);

        /**
         * Constructs a new shader as a copy of an existing one.
         *
         * See assignment operator.
         */
        Shader(const Shader& other);

        /**
         * Constructs an initialized shader from in-memory code.
         */
        Shader(
            ::GLenum initShaderType,
            const std::string& initCode
        );

        /**
         * Destructor.
         */
        ~Shader();

        /**
         * Assignment operator.
         *
         * If the other shader is initialized, this shader will also be
         * initialized.
         */
        Shader& operator =(const Shader& other);
    };
}

#endif

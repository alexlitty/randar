#ifndef RANDAR_ENGINE_GPU_HPP
#define RANDAR_ENGINE_GPU_HPP

#include <stdexcept>
#include <GL/glew.h>
#include <GL/glx.h>
#include <randar/Math/Rect.hpp>
#include <randar/Render.hpp>
#include <randar/Render/Image.hpp>
#include <randar/Utility/glm.hpp>

namespace randar
{
    /**
     * An interface with a GPU driver.
     *
     * Each instance represents a context.
     */
    class Gpu
    {
    protected:
        ::Display *display;
        ::GLXFBConfig *fbConfig;
        ::GLXPbuffer pbuffer;
        ::XVisualInfo *visualInfo;
        ::GLXContext context;

        Dimensional2<uint32_t> pbufferDimensions;

    public:
        Gpu();
        ~Gpu();

        /**
         * Makes the context of this GPU current.
         */
        void use();

        /**
         * Initializes a resource on the GPU.
         *
         * Nothing happens if the resource is already initialized.
         */
        void initialize(Shader& shader);
        void initialize(ShaderProgram& program);
        void initialize(VertexArray& vertexArray);

        /**
         * Destroys a resource on the GPU.
         *
         * Throws an error if the resource is not initialized yet.
         */
        void destroy(Shader& shader);
        void destroy(ShaderProgram& program);
        void destroy(VertexArray& vertexArray);

        /**
         * Gets the location of a shader program uniform.
         *
         * Returns -1 if the uniform is not used by the program.
         */
        ::GLint getUniformLocation(
            const ShaderProgram& program,
            const std::string& name);

        /**
         * Sets the value of a shader program uniform.
         *
         * Nothing happens if the uniform location is -1.
         */
        void setUniform(
            const ShaderProgram& program,
            ::GLint location,
            const glm::mat4& matrix);

        void setUniform(
            const ShaderProgram& program,
            ::GLint location,
            int integer);

        /**
         * Performs a sanity check.
         *
         * If the GPU is in a bad state, throws an error.
         */
        void check();

        /**
         * Waits until all commands have been processed by the GPU.
         */
        void finish();
    };
}

#endif

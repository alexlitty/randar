#ifndef RANDAR_RENDER_GPU_HPP
#define RANDAR_RENDER_GPU_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <randar/render/Canvas.hpp>
#include <randar/render/ShaderProgram.hpp>
#include <randar/render/Texture.hpp>

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
        void bindFramebuffer();

        void bindTexture(const Texture& texture);
        ::GLuint boundTexture;

        GLFWwindow *window;

    public:
        Gpu();
        ~Gpu();

        ::GLFWwindow& getWindow();

        /**
         * Texture construction and destruction.
         */
        Texture* createTexture(unsigned int width, unsigned int height);
        void destroyTexture(Texture* texture);

        /**
         * Texture manipulation.
         */
        void setTextureData(const Texture& texture, const GLvoid* data);
        void clearTexture(const Texture& texture);

        /**
         * Shader construction and destruction.
         */
        Shader* createShader(const std::string code, GLenum type);
        void destroyShader(Shader* shader);

        /**
         * Shader program construction and destruction.
         */
        ShaderProgram* createShaderProgram();

        /**
         * Drawing.
         */
        void draw(const Canvas& canvas, const Model& model);
        void draw(const Canvas& canvas, const Mesh& mesh);
        void draw(const Canvas& canvas, const Vertices& vertices);
    };

    /**
     * Retrieves the default GPU context.
     */
    Gpu& getDefaultGpu();
}

#endif

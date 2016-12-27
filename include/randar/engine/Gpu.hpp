#ifndef RANDAR_ENGINE_GPU_HPP
#define RANDAR_ENGINE_GPU_HPP

#include <randar/Render.hpp>

namespace randar
{
    class Canvas;

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
        Shader* createShader(const std::string& code, GLenum type);
        void destroyShader(Shader* shader);

        /**
         * Shader program construction and destruction.
         */
        ShaderProgram* createShaderProgram(
            const Shader& vertexShader,
            const Shader& fragmentShader
        );
        void destroyShaderProgram(ShaderProgram* shaderProgram);

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

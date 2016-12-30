#ifndef RANDAR_ENGINE_GPU_HPP
#define RANDAR_ENGINE_GPU_HPP

#include <randar/Render.hpp>

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
        Framebuffer defaultFramebuffer;
        void bindFramebuffer(const Framebuffer& framebuffer);
        ::GLuint boundFramebuffer;

        void bindVertices(const Vertices& vertices);
        void bindMesh(const Mesh& mesh);

        void bindTexture(const Texture& texture);
        ::GLuint boundTexture;

        GLFWwindow *window;

    public:
        Gpu();
        ~Gpu();

        ::GLFWwindow& getWindow();

        /**
         * Framebuffers.
         */
        const Framebuffer& getDefaultFramebuffer() const;
        Framebuffer& getDefaultFramebuffer();

        void clear(const Framebuffer& framebuffer, const Color& color);

        /**
         * Texture construction and destruction.
         */
        Texture* createTexture(randar::Texture::Type type, unsigned int width, unsigned int height);
        void destroyTexture(Texture* texture);

        /**
         * Texture manipulation.
         */
        void setTextureData(const Texture& texture, const GLvoid* data);
        void clearTexture(const Texture& texture);

        /**
         * Shaders.
         */
        Shader* createShader(const std::string& code, GLenum type);
        void destroyShader(Shader* shader);

        /**
         * Shader programs.
         */
        ShaderProgram* createShaderProgram(
            const Shader& vertexShader,
            const Shader& fragmentShader
        );
        void destroyShaderProgram(ShaderProgram* shaderProgram);

        /**
         * Drawing.
         */
        void draw(const Framebuffer& framebuffer, const Model& model);
    };

    /**
     * Retrieves the default GPU context.
     */
    Gpu& getDefaultGpu();
}

#endif

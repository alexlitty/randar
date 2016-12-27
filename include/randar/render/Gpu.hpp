#ifndef RANDAR_RENDER_GPU_HPP
#define RANDAR_RENDER_GPU_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <randar/render/Canvas.hpp>
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

        Texture* createTexture(unsigned int width, unsigned int height);
        void destroyTexture(Texture* texture);

        void setTexture(const Texture& texture, const GLvoid* data);
        void clearTexture(const Texture& texture);

        void draw(const Canvas& canvas, const Model& model);
        void draw(const Canvas& canvas, const Mesh& mesh);
        void draw(const Canvas& canvas, const Vertices& vertices);
    };

    /**
     * Retrieve a default GPU context.
     */
    Gpu& getDefaultGpu();
}

#endif

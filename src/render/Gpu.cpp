#include <randar/render/Gpu.hpp>

#include <iostream>
randar::Gpu::Gpu()
{
    // Initialize GLFW.
    if (!::glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    ::glfwWindowHint(GLFW_SAMPLES, 0);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = ::glfwCreateWindow(800, 600, "Randar", NULL, NULL);
    if (!this->window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    ::glfwMakeContextCurrent(this->window);

    // Initialize GLEW.
    ::glewExperimental = true;
    if (::glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // @todo - Ignore driver error. Investigate later.
    if (::glGetError() != GL_NO_ERROR) {

    }

    // Configure OpenGL.
    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LESS);
}

randar::Gpu::~Gpu()
{
    ::glfwDestroyWindow(this->window);
}

::GLFWwindow& randar::Gpu::getWindow()
{
    return *this->window;
}

randar::Texture* randar::Gpu::createTexture(unsigned int width, unsigned int height)
{
    GLuint glName;
    ::glGenTextures(1, &glName);

    Texture *texture = new Texture(glName, Texture::DEPTH, width, height);
    this->bindTexture(*texture);
    this->clearTexture(*texture);

    switch (texture->type) {
        case Texture::DEPTH:
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;

        default:
            throw std::runtime_error("Creating invalid texture type");
    }

    return texture;
}

void randar::Gpu::bindTexture(const randar::Texture& texture)
{
    if (texture.glName != boundTexture) {
        ::glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void randar::Gpu::setTexture(const randar::Texture& texture, const GLvoid* data)
{
    this->bindTexture(texture);

    switch (texture.type) {
        case Texture::DEPTH:
            ::glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_DEPTH_COMPONENT,
                texture.width,
                texture.height,
                0,
                GL_DEPTH_COMPONENT,
                GL_FLOAT,
                data
            );
            break;

        default:
            throw std::runtime_error("Setting data on invalid texture type");
    }
}

void randar::Gpu::clearTexture(const randar::Texture& texture)
{
    this->setTexture(texture, nullptr);
}

randar::Gpu& randar::getDefaultGpu()
{
    static Gpu defaultGpu;
    return defaultGpu;
}

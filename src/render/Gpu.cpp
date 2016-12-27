#include <randar/render/Gpu.hpp>

// Construction.
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

// Texture construction and destruction.
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

void randar::Gpu::destroyTexture(Texture* texture)
{
    ::glDeleteTextures(1, &texture->glName);
    delete texture;
}

// Texture binding.
void randar::Gpu::bindTexture(const randar::Texture& texture)
{
    if (texture.glName != boundTexture) {
        ::glBindTexture(GL_TEXTURE_2D, texture);
    }
}

// Texture manipulation.
void randar::Gpu::setTextureData(const randar::Texture& texture, const GLvoid* data)
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
    this->setTextureData(texture, nullptr);
}

// Shader creation and destruction.
randar::Shader* randar::Gpu::createShader(const std::string& code, GLenum type)
{
    GLint compileStatus, logLength;
    Shader *shader = new Shader(
        ::glCreateShader(type),
        type,
        code
    );

    const char *rawCode = shader->code.c_str();
    ::glShaderSource(*shader, 1, &rawCode, nullptr);
    ::glCompileShader(*shader);

    ::glGetShaderiv(*shader, GL_COMPILE_STATUS, &compileStatus);
    ::glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (compileStatus == GL_FALSE) {
        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];
            ::glGetShaderInfoLog(*shader, logLength, nullptr, log);

            std::string safeLog(log);
            delete[] log;
            throw std::runtime_error(safeLog);
        } else {
            throw std::runtime_error("Cannot compile shader, no log available");
        }
    }

    return shader;
}

void randar::Gpu::destroyShader(randar::Shader* shader)
{
    ::glDeleteShader(shader->glName);
    delete shader;
}

// Shader program creation and destruction.
randar::ShaderProgram* randar::Gpu::createShaderProgram(
    const randar::Shader& vertexShader,
    const randar::Shader& fragmentShader)
{
    GLint linkStatus, logLength;
    ShaderProgram *program = new ShaderProgram(
        ::glCreateProgram()
    );

    ::glAttachShader(*program, vertexShader);
    ::glAttachShader(*program, fragmentShader);
    ::glLinkProgram(*program);

    ::glGetProgramiv(*program, GL_LINK_STATUS, &linkStatus);
    ::glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &logLength);
    if (linkStatus == GL_FALSE) {
        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];
            ::glGetProgramInfoLog(*program, logLength, nullptr, log);

            std::string safeLog(log);
            delete[] log;
            throw std::runtime_error(safeLog);
        } else {
            throw std::runtime_error("Cannot link shader, no log available");
        }
    }

    ::glDetachShader(*program, vertexShader);
    ::glDetachShader(*program, fragmentShader);

    return program;
}

// Drawing.
//void randar::Gpu::draw(const randar::Canvas& canvas, const randar::Model& model)
//{
    //this->draw(canvas, model.mesh);
//}

//void randar::Gpu::draw(const randar::Canvas& canvas, const Mesh& mesh);
//void randar::Gpu::draw(const randar::Canvas& canvas, const Vertices& vertices);

// Retrieves the default GPU context.
randar::Gpu& randar::getDefaultGpu()
{
    static Gpu defaultGpu;
    return defaultGpu;
}

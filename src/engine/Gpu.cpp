#include <randar/engine/Gpu.hpp>

// Construction.
randar::Gpu::Gpu()
: defaultFramebuffer(0, randar::Viewport(0, 0, 800, 600))
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

// Vertices.
void randar::Gpu::bindVertices(const randar::Vertices& vertices)
{
    ::glBindBuffer(GL_ARRAY_BUFFER, vertices.vertexBuffer);
}

// Mesh.
void randar::Gpu::bindMesh(const randar::Mesh& mesh)
{
    this->bindVertices(mesh.vertices);
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);
}

// Framebuffers.
const randar::Framebuffer& randar::Gpu::getDefaultFramebuffer() const
{
    return this->defaultFramebuffer;
}

randar::Framebuffer& randar::Gpu::getDefaultFramebuffer()
{
    return this->defaultFramebuffer;
}

// Framebuffer binding.
void randar::Gpu::bindFramebuffer(const randar::Framebuffer& framebuffer)
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    const Viewport &viewport = framebuffer.camera.viewport;
    ::glViewport(viewport.x1, viewport.y1, viewport.x2, viewport.y2);
}

// Framebuffer manipulation.
void randar::Gpu::clear(const randar::Framebuffer& framebuffer, const randar::Color& color)
{
    ::glClearColor(color.r, color.g, color.b, color.a);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Drawing.
void randar::Gpu::draw(const randar::Framebuffer& framebuffer, const randar::Model& model)
{
    if (!model.shaderProgram) {
        throw std::runtime_error("Cannot draw without shader program");
    }
    this->bindFramebuffer(framebuffer);

    // Set MVP uniform.
    glm::mat4 mvp = framebuffer.camera.getProjectionMatrix()
        * framebuffer.camera.getViewMatrix()
        * model.getTransformMatrix();

    const ShaderProgram& shaderProgram = *model.shaderProgram;
    ::glUseProgram(shaderProgram);
    ::GLuint mvpId = ::glGetUniformLocation(shaderProgram, "mvp");
    ::glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);

    // Set joints uniform.
    if (model.joints.size()) {
        glm::mat4 jointMatrices[model.joints.size()];
        for (unsigned int i = 0; i < model.joints.size(); i++) {
            jointMatrices[i] = model.joints[i]->getPoseMatrix();
        }

        ::glUniformMatrix4fv(
            ::glGetUniformLocation(shaderProgram, "joints"),
            model.joints.size(),
            GL_FALSE,
            &jointMatrices[0][0][0]
        );
    }

    // Draw model.
    this->bindMesh(model.mesh);
    ::glDrawElements(
        GL_TRIANGLES,
        model.mesh.indices.size(),
        GL_UNSIGNED_INT,
        (void*)0
    );
}

// Retrieves the default GPU context.
randar::Gpu& randar::getDefaultGpu()
{
    static Gpu defaultGpu;
    return defaultGpu;
}

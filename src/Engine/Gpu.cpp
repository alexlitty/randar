#include <randar/Engine/Gpu.hpp>
#include <randar/Render/Model.hpp>

// Construction.
randar::Gpu::Gpu()
: defaultFramebuffer(randar::Viewport(0, 0, 800, 600))
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

// Destruction.
randar::Gpu::~Gpu()
{
    ::glfwDestroyWindow(this->window);
}

// Retrieves the default window.
::GLFWwindow& randar::Gpu::getWindow()
{
    return *this->window;
}

// Retrieves the default framebuffer.
const randar::Framebuffer& randar::Gpu::getDefaultFramebuffer() const
{
    return this->defaultFramebuffer;
}

randar::Framebuffer& randar::Gpu::getDefaultFramebuffer()
{
    return this->defaultFramebuffer;
}

// Initializes a GPU resource.
void randar::Gpu::initialize(randar::GpuResource* resource)
{
    if (resource->initialized) {
        return;
    }

    switch (resource->getType()) {
        case Resource::FRAMEBUFFER:
            this->initialize(*dynamic_cast<Framebuffer*>(resource));
            break;

        case Resource::SHADER:
            this->initialize(*dynamic_cast<Shader*>(resource));
            break;

        case Resource::SHADER_PROGRAM:
            this->initialize(*dynamic_cast<ShaderProgram*>(resource));
            break;

        case Resource::TEXTURE:
            this->initialize(*dynamic_cast<Texture*>(resource));
            break;

        default:
            throw std::runtime_error("Initializing invalid GPU resource");
            break;
    }
}

// Initializes a framebuffer.
void randar::Gpu::initialize(randar::Framebuffer& framebuffer)
{
    if (framebuffer.initialized) {
        return;
    }

    // Initialize framebuffer.
    ::glGenFramebuffers(1, framebuffer);
    this->bind(framebuffer);

    // Initialize attachments, add them to the framebuffer.
    Texture *texture = framebuffer.getTexture();
    if (texture) {
        this->initialize(*texture);
        this->bind(*texture);

        switch (texture->textureType) {
            case Texture::DEPTH:
                ::glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *texture, 0);
                break;

            case Texture::RGBA:
                ::glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *texture, 0);
                break;

            default:
                throw std::runtime_error("Adding invalid texture to framebuffer");
                break;
        }
    }

    ::glDrawBuffer(GL_NONE);

    if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Incomplete framebuffer");
    }
    framebuffer.initialized = true;
}

// Initializes a shader.
void randar::Gpu::initialize(randar::Shader& shader)
{
    if (shader.initialized) {
        return;
    }

    GLint compileStatus, logLength;
    shader.setGlName(::glCreateShader(shader.shaderType));

    const char *rawCode = shader.code.c_str();
    ::glShaderSource(shader, 1, &rawCode, nullptr);
    ::glCompileShader(shader);

    ::glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    ::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (compileStatus == GL_FALSE) {
        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];
            ::glGetShaderInfoLog(shader, logLength, nullptr, log);

            std::string safeLog(log);
            delete[] log;
            throw std::runtime_error(safeLog);
        } else {
            throw std::runtime_error("Cannot compile shader. No log available");
        }
    }

    shader.initialized = true;
}

// Initializes a shader program.
void randar::Gpu::initialize(randar::ShaderProgram& program)
{
    if (program.initialized) {
        return;
    }

    // Initialize dependencies.
    this->initialize(program.vertexShader);
    this->initialize(program.fragmentShader);

    GLint linkStatus, logLength;
    program.setGlName(::glCreateProgram());

    ::glAttachShader(program, program.vertexShader);
    ::glAttachShader(program, program.fragmentShader);
    ::glLinkProgram(program);

    ::glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    ::glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (linkStatus == GL_FALSE) {
        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];
            ::glGetProgramInfoLog(program, logLength, nullptr, log);

            std::string safeLog(log);
            delete[] log;
            throw std::runtime_error(safeLog);
        } else {
            throw std::runtime_error("Cannot link shader, no log available");
        }
    }

    ::glDetachShader(program, program.vertexShader);
    ::glDetachShader(program, program.fragmentShader);

    program.initialized = true;
}

// Initializes a texture.
void randar::Gpu::initialize(randar::Texture& texture)
{
    if (texture.initialized) {
        return;
    }

    ::glGenTextures(1, texture);
    this->bind(texture);
    this->clear(texture);

    switch (texture.textureType) {
        default:
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
    }

    texture.initialized = true;
}

// Initializes a vertex buffer.
void randar::Gpu::initialize(randar::VertexBuffer& buffer)
{
    if (buffer.initialized) {
        return;
    }

    ::glGenVertexArrays(1, buffer.vertexArray);
    ::glBindVertexArray(buffer.vertexArray);

    ::glGenBuffers(1, buffer);
    ::glBindBuffer(GL_ARRAY_BUFFER, buffer);

    unsigned int stride = Vertex::stride * sizeof(GLfloat);

    // Position.
    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)0
    );  

    // Color.
    ::glEnableVertexAttribArray(1);
    ::glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(3 * sizeof(GLfloat))
    );  

    // Bone index.
    ::glEnableVertexAttribArray(2);
    ::glVertexAttribPointer(
        2,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(7 * sizeof(GLfloat))
    );  

    // Bone weights.
    ::glEnableVertexAttribArray(3);
    ::glVertexAttribPointer(
        3,
        4,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(11 * sizeof(GLfloat))
    );

    // Texture coordinates.
    ::glEnableVertexAttribArray(4);
    ::glVertexAttribPointer(
        4,
        2,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)(15 * sizeof(GLfloat))
    );

    buffer.initialized = true;
}

// Destroys a GPU resource.
void randar::Gpu::destroy(randar::GpuResource* resource)
{
    // Resource is not initialized on the GPU. Nothing to destroy.
    if (!resource->initialized) {
        return;
    }

    switch (resource->getType()) {
        case Resource::FRAMEBUFFER:
            ::glDeleteFramebuffers(1, *resource);
            break;

        case Resource::SHADER:
            ::glDeleteShader(*resource);
            break;

        case Resource::SHADER_PROGRAM:
            ::glDeleteProgram(*resource);
            break;

        case Resource::TEXTURE:
            ::glDeleteTextures(1, *resource);
            break;

        case Resource::VERTEXBUFFER:
            VertexBuffer *buffer = dynamic_cast<VertexBuffer*>(resource);
            ::glDeleteBuffers(1, *resource);
            ::glDeleteVertexArrays(1, *resource);
            break;

        default:
            throw std::runtime_error("Destroying invalid GPU resource");
    }

    resource->initialized = false;
}

// Clears a framebuffer.
void randar::Gpu::clear(const randar::Framebuffer& framebuffer, const randar::Color& color)
{
    ::glClearColor(color.r, color.g, color.b, color.a);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Clears a texture.
void randar::Gpu::clear(const randar::Texture& texture)
{
    this->setTextureData(texture, nullptr);
}

// Writes an image to a texture.
void randar::Gpu::write(const randar::Texture& texture, const GLvoid* data)
{
    this->bind(texture);

    switch (texture.textureType) {
        case Texture::RGBA:
            ::glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                texture.width,
                texture.height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
            );
            break;

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

// Writes vertices to a vertex buffer.
void randar::Gpu::write(const randar::VertexBuffer& buffer, const std::vector<Vertex>& data)
{
    unsigned int count = data.size();
    GLfloat *data = new GLfloat[count * Vertex::stride];
    for (unsigned int i = 0; i < count; i++) {
        data[i].appendTo(&data[i * Vertex::stride]);
    }

    ::glBindBuffer(GL_ARRAY_BUFFER, buffer);
    ::glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    delete[] data;
}

// Binds a framebuffer.
void randar::Gpu::bind(const randar::Framebuffer& framebuffer)
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    const Viewport &viewport = framebuffer.camera.viewport;
    ::glViewport(viewport.x1, viewport.y1, viewport.x2, viewport.y2);
}

// Binds the vertices and faces of a mesh.
void randar::Gpu::bind(const randar::Mesh& mesh)
{
    this->bind(mesh.vertices);
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);
}

// Binds a texture.
void randar::Gpu::bind(const randar::Texture& texture)
{
    if (texture.getGlName() != boundTexture) {
        ::glBindTexture(GL_TEXTURE_2D, texture);
    }
}

// Binds a vertex buffer.
void randar::Gpu::bind(const randar::VertexBuffer& buffer)
{
    ::glBindVertexArray(buffer.vertexArray);
}

// Drawing.
void randar::Gpu::draw(const randar::Framebuffer& framebuffer, const randar::Model& model)
{
    const ShaderProgram& shaderProgram = model.get<ShaderProgram>();
    this->bind(framebuffer);

    // Set MVP uniform.
    glm::mat4 mvp = framebuffer.camera.getProjectionMatrix()
        * framebuffer.camera.getViewMatrix()
        * model.getTransformMatrix();

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
    //this->bind(model.mesh);
    /*::glDrawElements(
        GL_TRIANGLES,
        model.mesh.indices.size(),
        GL_UNSIGNED_INT,
        (void*)0
    );*/
}

// Retrieves the default GPU context.
randar::Gpu& randar::getDefaultGpu()
{
    static Gpu defaultGpu;
    return defaultGpu;
}

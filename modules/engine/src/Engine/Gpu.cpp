#include <randar/Engine/Gpu.hpp>
#include <randar/Render/DefaultTexture.hpp>

// Construction.
randar::Gpu::Gpu()
{
    this->pbufferDimensions.resize(800, 600);

    int fbAttribs[] = { 
        GLX_X_RENDERABLE, true,
        GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24, 
        GLX_STENCIL_SIZE, 8,
        GLX_DOUBLEBUFFER, false,
        None
    };

    int pbAttribs[] = {
        //GLX_PBUFFER_WIDTH, this->pbufferDimensions.getWidth(),
        //GLX_PBUFFER_HEIGHT, this->pbufferDimensions.getHeight(),
        None
    };

    // Create an OpenGL context.
    this->display = ::XOpenDisplay(nullptr);
    if (!this->display) {
        throw std::runtime_error("Failed to open X display");
    }

    int fbCount;
    this->fbConfig = ::glXChooseFBConfig(
        this->display,
        DefaultScreen(this->display),
        fbAttribs,
        &fbCount);
    if (fbCount == 0) {
        throw std::runtime_error("No framebuffers available");
    }

    this->pbuffer = ::glXCreatePbuffer(this->display, this->fbConfig[0], pbAttribs);
    if (!this->pbuffer) {
        throw std::runtime_error("Failed to create pixel buffer");
    }

    this->visualInfo = ::glXGetVisualFromFBConfig(this->display, this->fbConfig[0]);
    if (!this->visualInfo) {
        throw std::runtime_error("No appropriate visual found");
    }

    this->context = ::glXCreateContext(this->display, this->visualInfo, nullptr, true);
    if (!this->context) {
        throw std::runtime_error("Failed to create GLX context");
    }
    this->use();

    // Initialize GLEW.
    ::glewExperimental = true;
    GLenum status = ::glewInit();
    if (status != GLEW_OK) {
        throw std::runtime_error(
            "Failed to initialize GLEW: " + std::string(
                reinterpret_cast<const char*>(
                    ::glewGetErrorString(status)
                )
            )
        );
    }

    // Configure OpenGL.
    ::glEnable(GL_VERTEX_ARRAY);
    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LESS);

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Destruction.
randar::Gpu::~Gpu()
{
    ::glXDestroyContext(this->display, this->context);
    ::XFree(this->display);
    ::XFree(this->visualInfo);
}

// Makes the context of this GPU current.
void randar::Gpu::use()
{
    ::glXMakeCurrent(
        this->display,
        RootWindow(this->display, this->visualInfo->screen),
        this->context
    );
}

// Initializes an index buffer.
void randar::Gpu::initialize(randar::IndexBuffer& buffer)
{
    if (buffer.isInitialized()) {
        return;
    }

    ::glGenBuffers(1, buffer);
}

// Initializes a shader.
void randar::Gpu::initialize(randar::Shader& shader)
{
    if (shader.isInitialized()) {
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
}

// Initializes a shader program.
void randar::Gpu::initialize(randar::ShaderProgram& program)
{
    if (program.isInitialized()) {
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
}

// Initializes a vertex array.
// @todo - Make this into a useful function, out of vertex buffer initialization.
void randar::Gpu::initialize(randar::VertexArray& vertexArray)
{
    if (vertexArray.isInitialized()) {
        return;
    }

    ::glGenVertexArrays(1, vertexArray);
}

// Destroys an index buffer.
void randar::Gpu::destroy(randar::IndexBuffer& buffer)
{
    if (!buffer.isInitialized()) {
        throw std::runtime_error("Destroying index buffer that is not initialized");
    }
    ::glDeleteBuffers(1, buffer);
}

// Destroys a shader.
void randar::Gpu::destroy(randar::Shader& shader)
{
    if (!shader.isInitialized()) {
        throw std::runtime_error("Destroying shader that is not initialized");
    }
    ::glDeleteShader(shader);
}

// Destroys a shader program.
void randar::Gpu::destroy(randar::ShaderProgram& program)
{
    if (!program.isInitialized()) {
        throw std::runtime_error("Destroying shader program that is not initialized");
    }
    ::glDeleteProgram(program);
}

// Destroys a vertex array.
// @todo - Separate logic from vertex buffers.
void randar::Gpu::destroy(randar::VertexArray& vertexArray)
{
    if (!vertexArray.isInitialized()) {
        throw std::runtime_error("Destroying vertex array that is not initialized");
    }
}

// Writes indices to an index buffer.
void randar::Gpu::write(randar::IndexBuffer& indexBuffer, const std::vector<uint32_t>& indices)
{
    this->bind(indexBuffer);

    indexBuffer.count = indices.size();
    ::glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indexBuffer.count * sizeof(uint32_t),
        &indices.data()[0],
        GL_STATIC_DRAW
    );
}

// Gets the location of a shader program uniform.
::GLint randar::Gpu::getUniformLocation(
    const randar::ShaderProgram& program,
    const std::string& name)
{
    return ::glGetUniformLocation(program, name.c_str());
}

// Sets a uniform to a 4x4 matrix.
void randar::Gpu::setUniform(
    const randar::ShaderProgram& program,
    ::GLint location,
    const glm::mat4& matrix)
{
    ::glUseProgram(program);
    ::glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

// Sets a uniform to an integer.
void randar::Gpu::setUniform(
    const randar::ShaderProgram& program,
    ::GLint location,
    int integer)
{
    ::glUseProgram(program);
    ::glUniform1i(location, integer);
}

// Binds an index buffer.
void randar::Gpu::bind(const randar::IndexBuffer& buffer)
{
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

// Drawing.
/*void randar::Gpu::draw(
    ShaderProgram& program,
    randar::Framebuffer& framebuffer,
    randar::Model& model)
{
    if (!program.isInitialized()) {
        throw std::runtime_error("Drawing model with uninitialized shader program");
    }

    if (!model.isInitialized()) {
        this->write(model);
    }

    framebuffer.bind();

    // Set MVP uniform.
    glm::mat4 mvp = framebuffer.camera.getProjectionMatrix()
        * framebuffer.camera.getViewMatrix()
        * model.getTransformMatrix();
    program.setUniform("mvp", mvp);

    // Set joints uniform.
    size_t jointCount = model.joints.size();
    if (jointCount) {
        // TODO Is there a way to allocate this on the stack instead?
        glm::mat4* jointMatrices = new glm::mat4[jointCount];
        for (unsigned int i = 0; i < model.joints.size(); i++) {
            jointMatrices[i] = model.joints[i]->getPoseMatrix();
        }

        delete[] jointMatrices;

        ::glUniformMatrix4fv(
            ::glGetUniformLocation(program, "joints"),
            model.joints.size(),
            GL_FALSE,
            &jointMatrices[0][0][0]
        );
    }

    // Set textures.
    for (uint16_t i = 0; i < model.meshTextures.size(); i++) {
        Texture *texture = model.meshTextures[i];

        if (!texture) {
            //texture = &randar::getDefaultTexture(*this, "rgba", 1, 1);
        }

        ::glActiveTexture(GL_TEXTURE0 + i);
        texture->bind();

        program.setUniform("meshTexture" + std::to_string(i), i);
    }

    // Draw model.
    ::glUseProgram(program);

    this->bind(model);
    ::glDrawElements(
        GL_TRIANGLES,
        model.faceBuffer.count,
        GL_UNSIGNED_INT,
        (void*)0
    );
}*/

// Performs a sanity check.
void randar::Gpu::check()
{
    ::GLenum error = ::glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("OpenGL error: " + std::to_string(error));
    }
}

// Waits until all commands have been processed by the GPU.
void randar::Gpu::finish()
{
    ::glFinish();
}

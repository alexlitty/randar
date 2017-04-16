#include <randar/Engine/Gpu.hpp>
#include <randar/Render/DefaultTexture.hpp>



// Construction.
randar::Gpu::Gpu()
{
    static int attribs[] = { 
        GLX_X_RENDERABLE, true,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
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

    // Create an OpenGL context.
    this->display = ::XOpenDisplay(nullptr);
    if (!this->display) {
        throw std::runtime_error("Failed to open X display");
    }

    int fbcount;
    ::GLXFBConfig *fbc = ::glXChooseFBConfig(
        this->display,
        DefaultScreen(this->display),
        attribs,
        &fbcount);
    if (fbcount == 0) {
        throw std::runtime_error("No framebuffers available");
    }

    this->visualInfo = ::glXGetVisualFromFBConfig(this->display, fbc[0]);
    ::XFree(fbc);
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

// Initializes a framebuffer.
void randar::Gpu::initialize(randar::Framebuffer& framebuffer)
{
    if (framebuffer.isInitialized()) {
        return;
    }

    // Initialize framebuffer.
    ::glGenFramebuffers(1, framebuffer);
    this->bind(framebuffer);

    // Initialize framebuffer texture.
    if (framebuffer.hasTexture()) {
        Texture& texture = framebuffer.getTexture();

        this->initialize(texture);
        this->bind(texture);

        // Attach RGBA texture.
        if (texture.isRgba()) {
            ::glFramebufferTexture(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                texture,
                0
            );

            ::GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
            ::glDrawBuffers(1, drawBuffers);
        }

        // Attach depth texture.
        else if (texture.isDepth()) {
            ::glFramebufferTexture(
                GL_FRAMEBUFFER,
                GL_DEPTH_ATTACHMENT,
                texture,
                0
            );

            ::glDrawBuffer(GL_NONE);
        }

        // Invalid texture.
        else {
            throw std::runtime_error("Configuring framebuffer with invalid texture type");
        }
    }

    // Initialize framebuffer depth buffer.
    if (framebuffer.hasDepthBuffer()) {
        this->initialize(framebuffer.getDepthBuffer());
        this->bind(framebuffer.getDepthBuffer());
    }

    // Check for errors.
    if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Error while initializing framebuffer");
    }
}

// Initializes an index buffer.
void randar::Gpu::initialize(randar::IndexBuffer& buffer)
{
    if (buffer.isInitialized()) {
        return;
    }

    ::glGenBuffers(1, buffer);
}

// Initializes a renderbuffer.
void randar::Gpu::initialize(randar::Renderbuffer& renderbuffer)
{
    if (renderbuffer.isInitialized()) {
        return;
    }

    ::glGenRenderbuffers(1, renderbuffer);
    this->bind(renderbuffer);

    ::glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT,
        renderbuffer.width,
        renderbuffer.height
    );
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

// Initializes a texture.
void randar::Gpu::initialize(randar::Texture& texture)
{
    if (texture.isInitialized()) {
        return;
    }

    ::glGenTextures(1, texture);
    this->check();

    this->bind(texture);

    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (texture.data.size()) {
        this->write(texture);
    }

    // No data provided. Initialize the texture with arbitrary content.
    else {
        this->clear(texture);
    }
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

// Initializes a vertex buffer.
void randar::Gpu::initialize(randar::VertexBuffer& buffer)
{
    if (buffer.isInitialized()) {
        return;
    }

    ::glGenVertexArrays(1, buffer.vertexArray);
    ::glBindVertexArray(buffer.vertexArray);

    ::glGenBuffers(1, buffer);
    ::glBindBuffer(GL_ARRAY_BUFFER, buffer);

    unsigned int stride = Vertex().stride * sizeof(GLfloat);

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
}

// Resizes a framebuffer.
void randar::Gpu::resize(randar::Framebuffer& framebuffer)
{
    uint32_t width = framebuffer.getWidth();
    uint32_t height = framebuffer.getHeight();

    framebuffer.camera.viewport = Viewport(0, 0, width, height);

    if (framebuffer.hasTexture()) {
        framebuffer.getTexture().resize(width, height);
    }

    if (framebuffer.hasDepthBuffer()) {
        this->resize(framebuffer.getDepthBuffer(), width, height);
    }
}

// Resizes a renderbuffer.
void randar::Gpu::resize(randar::Renderbuffer& renderbuffer, unsigned int width, unsigned int height)
{
    renderbuffer.width  = width;
    renderbuffer.height = height;

    this->bind(renderbuffer);
    ::glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT,
        renderbuffer.width,
        renderbuffer.height
    );
}

// Resizes a texture.
void randar::Gpu::resize(randar::Texture& texture)
{
    // Since we send the dimensions with texture data, just clear the texture.
    this->clear(texture);
}

// Destroys a framebuffer.
void randar::Gpu::destroy(randar::Framebuffer& framebuffer)
{
    if (!framebuffer.isDefault()) {
        if (!framebuffer.isInitialized()) {
            throw std::runtime_error("Destroying framebuffer that is not initialized");
        }
        ::glDeleteFramebuffers(1, framebuffer);
    }
}

// Destroys an index buffer.
void randar::Gpu::destroy(randar::IndexBuffer& buffer)
{
    if (!buffer.isInitialized()) {
        throw std::runtime_error("Destroying index buffer that is not initialized");
    }
    ::glDeleteBuffers(1, buffer);
}

// Destroys a renderbuffer.
void randar::Gpu::destroy(randar::Renderbuffer& renderbuffer)
{
    if (!renderbuffer.isInitialized()) {
        throw std::runtime_error("Destroying renderbuffer that is not initialized");
    }
    ::glDeleteRenderbuffers(1, renderbuffer);
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

// Destroys a texture.
void randar::Gpu::destroy(randar::Texture& texture)
{
    if (!texture.isInitialized()) {
        throw std::runtime_error("Destroying texture that is not initialized");
    }
    ::glDeleteTextures(1, texture);
}

// Destroys a vertex array.
// @todo - Separate logic from vertex buffers.
void randar::Gpu::destroy(randar::VertexArray& vertexArray)
{
    if (!vertexArray.isInitialized()) {
        throw std::runtime_error("Destroying vertex array that is not initialized");
    }
}

// Destroys a vertex buffer.
void randar::Gpu::destroy(randar::VertexBuffer& buffer)
{
    if (!buffer.isInitialized()) {
        throw std::runtime_error("Destroying vertex buffer that is not initialized");
    }
    ::glDeleteBuffers(1, buffer);
}

// Clears a framebuffer.
void randar::Gpu::clear(const randar::Framebuffer& framebuffer, const randar::Color& color)
{
    this->bind(framebuffer);
    ::glClearColor(color.r(), color.g(), color.b(), color.a());
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Clears a texture.
void randar::Gpu::clear(const randar::Texture& texture)
{
    this->write(texture, nullptr, GL_RGBA);
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

// Writes an image to a texture.
void randar::Gpu::write(const randar::Texture& texture)
{
    this->write(texture, texture.data.data(), GL_RGBA);
}

void randar::Gpu::write(const randar::Texture& texture, const GLvoid* data, GLenum dataFormat)
{
    this->bind(texture);

    if (texture.isRgba()) {
        ::glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            texture.getWidth(),
            texture.getHeight(),
            0,
            dataFormat,
            GL_UNSIGNED_BYTE,
            data
        );
    }

    else if (texture.isDepth()) {
        ::glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_DEPTH_COMPONENT,
            texture.getWidth(),
            texture.getHeight(),
            0,
            GL_DEPTH_COMPONENT,
            GL_FLOAT,
            data
        );
    }

    else {
        throw std::runtime_error("Writing data to invalid texture type");
    }

    this->check();
}

void randar::Gpu::write(
    const randar::Texture& texture,
    const randar::Rect<uint32_t>& rect,
    const GLvoid* data,
    GLenum dataFormat)
{
    this->bind(texture);

    if (texture.isRgba()) {
        ::glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            rect.left,
            rect.top,
            rect.width,
            rect.height,
            dataFormat,
            GL_UNSIGNED_BYTE,
            data
        );
    }

    else {
        throw std::runtime_error("Writing partial data to invalid texture type");
    }

    this->check();
}

// Writes vertices to a vertex buffer.
void randar::Gpu::write(const randar::VertexBuffer& buffer, const std::vector<Vertex>& vertices)
{
    unsigned int count = vertices.size();
    GLfloat *data = new GLfloat[count * Vertex().stride];
    for (unsigned int i = 0; i < count; i++) {
        GLfloat *subdata = &data[i * Vertex().stride];
        vertices[i].appendTo(subdata);
    }

    ::glBindBuffer(GL_ARRAY_BUFFER, buffer);
    ::glBufferData(GL_ARRAY_BUFFER, count * Vertex().stride * sizeof(GLfloat), data, GL_STATIC_DRAW);
    delete[] data;
}

// Writes model data to the GPU.
void randar::Gpu::write(randar::Model& model)
{
    this->initialize(model.vertexBuffer);
    this->write(model.vertexBuffer, model.vertices);

    this->initialize(model.faceBuffer);
    this->write(model.faceBuffer, model.faceIndices);
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

// Binds a framebuffer.
void randar::Gpu::bind(const randar::Framebuffer& framebuffer)
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    const Viewport &viewport = framebuffer.camera.viewport;
    ::glViewport(viewport.x1, viewport.y1, viewport.x2, viewport.y2);
}

// Binds an index buffer.
void randar::Gpu::bind(const randar::IndexBuffer& buffer)
{
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

// Binds the vertex and index buffers of a model's mesh.
void randar::Gpu::bind(const randar::Model& model)
{
    this->bind(model.vertexBuffer);
    this->bind(model.faceBuffer);

    // @todo - bind joints, textures and whatnot.
}

// Binds a renderbuffer.
void randar::Gpu::bind(const randar::Renderbuffer& renderbuffer)
{
    ::glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
}

// Binds a texture.
void randar::Gpu::bind(const randar::Texture& texture)
{
    ::glBindTexture(GL_TEXTURE_2D, texture);
}

// Binds a vertex buffer.
void randar::Gpu::bind(const randar::VertexBuffer& buffer)
{
    ::glBindVertexArray(buffer.vertexArray);
}

// Drawing.
void randar::Gpu::draw(
    ShaderProgram& program,
    const randar::Framebuffer& framebuffer,
    randar::Model& model)
{
    if (!program.isInitialized()) {
        throw std::logic_error("Drawing model with uninitialized shader program");
    }

    if (!model.isInitialized()) {
        this->write(model);
    }

    this->bind(framebuffer);

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

        /*::glUniformMatrix4fv(
            ::glGetUniformLocation(program, "joints"),
            model.joints.size(),
            GL_FALSE,
            &jointMatrices[0][0][0]
        );*/
    }

    // Set textures.
    for (uint16_t i = 0; i < model.meshTextures.size(); i++) {
        Texture *texture = model.meshTextures[i];

        if (!texture) {
            texture = &randar::getDefaultTexture("rgba", 1, 1);
        }

        ::glActiveTexture(GL_TEXTURE0 + i);
        this->bind(*texture);

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
}

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

// Retrieves the default GPU context.
randar::Gpu& randar::getDefaultGpu()
{
    static Gpu defaultGpu;
    return defaultGpu;
}

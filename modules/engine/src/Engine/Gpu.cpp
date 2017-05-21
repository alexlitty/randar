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

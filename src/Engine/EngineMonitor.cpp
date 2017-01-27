#include <randar/Engine/EngineMonitor.hpp>
#include <randar/Engine/Gpu.hpp>

randar::EngineMonitor::EngineMonitor()
: monitorFramebuffer("rgba", true),
  camera(monitorFramebuffer.camera),
  targetModel(nullptr)
{
    screenProgram.set(
        randar::Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/screen.vert")),
        randar::Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/screen.frag"))
    );

    modelProgram.set(
        randar::Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/monitor-model.vert")),
        randar::Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/monitor-model.frag"))
    );

    // Screen vertices.
    Vertex vertex;
    vertex.position.set(-0.5f, -1.0f, 0.001f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 1.0f;
    this->screen.vertices.push_back(vertex);

    vertex.position.set(-0.5f, 1.0f, 0.001f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 0.0f;
    this->screen.vertices.push_back(vertex);

    vertex.position.set(1.0f, -1.0f, 0.001f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 1.0f;
    this->screen.vertices.push_back(vertex);

    vertex.position.set(1.0f, 1.0f, 0.001f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 0.0f;
    this->screen.vertices.push_back(vertex);

    // Screen face indices.
    this->screen.faceIndices.push_back(0);
    this->screen.faceIndices.push_back(1);
    this->screen.faceIndices.push_back(2);

    this->screen.faceIndices.push_back(3);
    this->screen.faceIndices.push_back(1);
    this->screen.faceIndices.push_back(2);

    // Send screen model to the GPU.
    this->gpu.write(this->screen);

    // Initialize the UI size.
    this->resize();
}

randar::EngineMonitor::~EngineMonitor()
{

}

// Resizes the UI to fit the default window.
void randar::EngineMonitor::resize()
{
    int width, height;
    ::glfwGetWindowSize(&this->gpu.getWindow(), &width, &height);

    this->defaultFramebuffer.camera.viewport = randar::Viewport(0, 0, width, height);

    this->monitorFramebuffer.resize(width, height);
}

// Clears the current target.
void randar::EngineMonitor::clearTarget()
{
    this->targetModel = nullptr;
}

// Sets a model as the monitoring target.
void randar::EngineMonitor::setTarget(randar::Model& model)
{
    this->clearTarget();
    this->targetModel = &model;

    this->monitorFramebuffer.camera.setPosition(randar::Vector(0.0f, 8.0f, -30.0f));
    this->monitorFramebuffer.camera.setTarget(randar::Vector(0.1f, 0.1f, 0.1f));
}

// Draws the monitoring target.
void randar::EngineMonitor::draw()
{
    this->gpu.clear(this->defaultFramebuffer, Color(0.03f, 0.03f, 0.25f, 0.0f));
    this->gpu.clear(this->monitorFramebuffer, Color(0.03f, 0.03f, 0.25f, 0.0f));

    // Target is a model.
    if (this->targetModel) {
        this->gpu.draw(
            this->modelProgram,
            this->monitorFramebuffer,
            *this->targetModel
        );
    }

    // No target to draw.
    else {

    }

    // Draw monitor framebuffer onto screen model.
    this->gpu.bind(this->monitorFramebuffer.texture);
    this->gpu.draw(this->screenProgram, this->defaultFramebuffer, this->screen);
}

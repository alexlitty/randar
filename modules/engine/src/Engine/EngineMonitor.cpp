#include <algorithm>
#include <randar/Engine/EngineMonitor.hpp>
#include <randar/Engine/Gpu.hpp>

/*randar::EngineMonitor::EngineMonitor()
: newTarget(false),
  monitorFramebuffer("rgba", true),
  camera(this->monitorFramebuffer.camera)
{
    this->clearTarget();

    screenProgram.set(
        randar::Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/screen.vert")),
        randar::Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/screen.frag"))
    );

    modelProgram.set(
        randar::Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/monitor-model.vert")),
        randar::Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/monitor-model.frag"))
    );

    modelWireframeProgram.set(
        randar::Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/monitor-model-wireframe.vert")),
        randar::Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/monitor-model-wireframe.frag"))
    );

    textureProgram.set(
        randar::Shader(GL_VERTEX_SHADER, randar::readAsciiFile("./resources/shaders/monitor-texture.vert")),
        randar::Shader(GL_FRAGMENT_SHADER, randar::readAsciiFile("./resources/shaders/monitor-texture.frag"))
    );

    // Screen vertices.
    Vertex vertex;
    vertex.position.set(-1.0f, -1.0f, 0.000f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 0.0f;
    this->screen.vertices.push_back(vertex);

    vertex.position.set(-1.0f, 1.0f, 0.000f);
    vertex.textureCoordinate.u = 0.0f;
    vertex.textureCoordinate.v = 1.0f;
    this->screen.vertices.push_back(vertex);

    vertex.position.set(1.0f, -1.0f, 0.000f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 0.0f;
    this->screen.vertices.push_back(vertex);

    vertex.position.set(1.0f, 1.0f, 0.000f);
    vertex.textureCoordinate.u = 1.0f;
    vertex.textureCoordinate.v = 1.0f;
    this->screen.vertices.push_back(vertex);

    // Screen face indices.
    this->screen.faceIndices.push_back(0);
    this->screen.faceIndices.push_back(1);
    this->screen.faceIndices.push_back(2);

    this->screen.faceIndices.push_back(3);
    this->screen.faceIndices.push_back(1);
    this->screen.faceIndices.push_back(2);

    // Send models to the GPU.
    this->gpu.write(this->screen);
}

randar::EngineMonitor::~EngineMonitor()
{

}

// Resizes the monitor.
void randar::EngineMonitor::resize(uint32_t width, uint32_t height)
{
    this->monitorFramebuffer.resize(width, height);
}

// Clears the current target.
void randar::EngineMonitor::clearTarget()
{
    this->newTarget = false;

    this->targetModel = nullptr;
    this->targetTexture = nullptr;
}

// Sets a model as the monitoring target.
void randar::EngineMonitor::setTarget(randar::Model& model)
{
    this->clearTarget();
    this->newTarget = true;
    this->targetModel = &model;
}

void randar::EngineMonitor::setTarget(randar::Texture& texture)
{
    this->clearTarget();
    this->newTarget = true;
    this->targetTexture = &texture;

}

// Whether the monitoring target has been changed.
bool randar::EngineMonitor::hasNewTarget() const
{
    return this->newTarget;
}

// Initializes the current target onto the monitor.
void randar::EngineMonitor::initializeTarget()
{
    if (this->targetModel) {
        this->monitorFramebuffer.camera.disableOrtho();
        this->monitorFramebuffer.camera.setPosition(randar::Vector3(0.0f, 0.0f, -15.0f));
        this->monitorFramebuffer.camera.setTarget(randar::Vector3(0.0f, 0.0f, 0.0f));
    }

    else if (this->targetTexture) {
        int maxWidth = this->monitorFramebuffer.getWidth();
        int maxHeight = this->monitorFramebuffer.getHeight();

        int texWidth = this->targetTexture->getWidth();
        int texHeight = this->targetTexture->getHeight();
        float aspect = static_cast<float>(texWidth) / static_cast<float>(texHeight);

        float width, height;
        if (aspect > 0) {
            height = std::min(texHeight, maxHeight);
            width  = aspect * height;
        } else {
            width  = std::min(texWidth, maxWidth);
            height = width / aspect;
        }

        this->monitorFramebuffer.camera.setOrtho(0, maxWidth, maxHeight, 0);

        // Texture model vertices.
        this->targetTextureModel.vertices.clear();
        Vertex vertex;

        vertex.position.set(0, 0);
        vertex.textureCoordinate.u = 0.0f;
        vertex.textureCoordinate.v = 1.0f;
        this->targetTextureModel.vertices.push_back(vertex);

        vertex.position.set(0, height);
        vertex.textureCoordinate.u = 0.0f;
        vertex.textureCoordinate.v = 0.0f;
        this->targetTextureModel.vertices.push_back(vertex);

        vertex.position.set(width, 0);
        vertex.textureCoordinate.u = 1.0f;
        vertex.textureCoordinate.v = 1.0f;
        this->targetTextureModel.vertices.push_back(vertex);

        vertex.position.set(width, height);
        vertex.textureCoordinate.u = 1.0f;
        vertex.textureCoordinate.v = 0.0f;
        this->targetTextureModel.vertices.push_back(vertex);

        // Texture model face indices.
        this->targetTextureModel.faceIndices.clear();
        this->targetTextureModel.faceIndices.push_back(0);
        this->targetTextureModel.faceIndices.push_back(1);
        this->targetTextureModel.faceIndices.push_back(2);

        this->targetTextureModel.faceIndices.push_back(3);
        this->targetTextureModel.faceIndices.push_back(1);
        this->targetTextureModel.faceIndices.push_back(2);

        // Write texture model to GPU.
        this->gpu.write(this->targetTextureModel);
    }

    this->newTarget = false;
}

// Draws the monitoring target.
void randar::EngineMonitor::draw()
{
    this->monitorFramebuffer.clear(Color(0.0f, 0.0f, 0.0f, 0.0f));

    // Initialize the target if it is new.
    if (this->hasNewTarget()) {
        this->initializeTarget();
    }

    // Target is a model.
    if (this->targetModel) {
        ShaderProgram *program;

        if (this->targetModel->isMissingMeshTextures()) {
            program = &this->modelWireframeProgram;
        } else {
            program = &this->modelProgram;
        }

        this->gpu.draw(
            *program,
            this->monitorFramebuffer,
            *this->targetModel
        );
    }

    // Target is a texture.
    else if (this->targetTexture) {
        this->gpu.bind(*this->targetTexture);

        this->gpu.draw(
            this->textureProgram,
            this->monitorFramebuffer,
            this->targetTextureModel
        );
    }

    // No target to draw.
    else {

    }

    // Draw monitor framebuffer onto screen model.
    this->gpu.bind(this->monitorFramebuffer.getTexture());
    this->gpu.draw(this->screenProgram, this->defaultFramebuffer, this->screen);
}*/

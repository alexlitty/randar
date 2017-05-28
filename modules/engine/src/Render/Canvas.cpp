#include <randar/Render/Camcorder.hpp>
#include <randar/Render/Canvas.hpp>
#include <randar/Render/Framebuffer.hpp>

// Constructor.
randar::Canvas::Canvas(uint16_t initFps)
: canvasFps(initFps)
{

}

// Destructor.
randar::Canvas::~Canvas()
{
    for (auto watcher : this->watchers) {
        watcher->unwatch();
    }
}

// Sets and retrieves the desired fps.
void randar::Canvas::fps(uint16_t newFps)
{
    this->canvasFps = newFps;
}

uint16_t randar::Canvas::fps() const
{
    return this->canvasFps;
}

// Retrieves a reference to the canvas camera.
randar::Camera& randar::Canvas::camera()
{
    return this->canvasCamera;
}

// Clears the canvas with a color.
void randar::Canvas::clear(const randar::Color& color)
{
    this->framebuffer().bind();

    ::glClearColor(color.r(), color.g(), color.b(), color.a());
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Draws geometry to the canvas.
void randar::Canvas::draw(randar::Geometry& geometry)
{
    this->draw(geometry, this->framebuffer().context().defaultShaderProgram());
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::ShaderProgram& program)
{
    this->draw(geometry, Transform::Identity, program);
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::Transform& transform,
    randar::ShaderProgram& program)
{
    this->framebuffer().ensureContext();

    // Force the geometry onto the current context.
    if (!this->framebuffer().sameContext(geometry)) {
        geometry.initialize(this->framebuffer().context());
    }

    // Ensure any new geometry data is synced.
    geometry.sync();

    // Fill basic shader program uniforms.
    glm::mat4 mvp = this->camera().projectionMatrix()
                  * this->camera().viewMatrix()
                  * transform.transformMatrix();
    program.uniform("mvp", mvp);

    // Bind required resources for drawing.
    program.use();
    geometry.vertices.bind();
    geometry.indices.bind();
    this->framebuffer().bind();

    // Draw the geometry.
    ::glDrawElements(
        openglPrimitive(geometry.primitive),
        geometry.indices.count(),
        GL_UNSIGNED_INT,
        nullptr);
    this->framebuffer().context().check("Failed to draw");
}

// Draws a model to the canvas.
void randar::Canvas::draw(randar::Model& model)
{
    if (!model.hasGeometry()) {
        return;
    }

    ShaderProgram* program;
    if (model.hasShaderProgram()) {
        program = &model.shaderProgram();
    } else {
        program = &this->framebuffer().context().defaultShaderProgram();
    }

    this->draw(model.geometry(), model, *program);
}

// Retrieves the contents of this canvas as an image.
randar::Image randar::Canvas::image()
{
    Image result;

    this->framebuffer().bind();
    result.layout(Image::LAYOUT::FLIP_VERTICAL);
    result.resize(
        this->framebuffer().getWidth(),
        this->framebuffer().getHeight()
    );

    ::glReadPixels(
        0,
        0,
        result.getWidth(),
        result.getHeight(),
        GL_RGBA,
        GL_FLOAT,
        result.raw()
    );

    return result;
}

// Presents the canvas rendering.
void randar::Canvas::present()
{
    // Throttle execution to meet desired fps.
    if (this->canvasFps) {
        this->throttleTimer.wait(
            (1.0f / static_cast<float>(this->canvasFps)) * 1000 * 1000
        );
    }
    this->throttleTimer.reset();

    // Notify watchers.
    for (auto watcher : this->watchers) {
        watcher->onCanvasPresent();
    }
}

// Gets a new camcorder for this canvas.
randar::Camcorder randar::Canvas::camcorder()
{
    return randar::Camcorder(*this);
}

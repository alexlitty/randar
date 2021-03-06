#include <randar/Render/Camcorder.hpp>
#include <randar/Render/Canvas.hpp>
#include <randar/Render/Framebuffer.hpp>
#include <randar/Render/DefaultTexture.hpp>
#include <randar/Render/Light/LightCollection.hpp>
#include <randar/World/World.hpp>

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

    this->framebuffer().context().check("Cannot clear framebuffer");
}

// Draws geometry to the canvas.
void randar::Canvas::draw(randar::Geometry& geometry)
{
    this->draw(geometry, this->framebuffer().context().defaultShaderProgram());
}

void randar::Canvas::draw(randar::Geometry& geometry, randar::TextureCollection& textures)
{
    this->draw(
        geometry,
        textures,
        Transform::Identity,
        this->framebuffer().context().defaultShaderProgram()
    );
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::ShaderProgram& program)
{
    this->draw(geometry, Transform::Identity, program);
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::Transform& transform)
{
    this->draw(geometry, transform, this->framebuffer().context().defaultShaderProgram());
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::Transform& transform,
    randar::ShaderProgram& program)
{
    TextureCollection textures;
    this->draw(geometry, textures, transform, program);
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::Transform& transform,
    randar::LightCollection& lights,
    randar::ShaderProgram& program)
{
    TextureCollection textures;
    this->draw(geometry, textures, transform, lights, program);
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::TextureCollection& textures,
    randar::Transform& transform,
    randar::ShaderProgram& program)
{
    LightCollection lights;
    this->draw(geometry, textures, transform, lights, program);
}

void randar::Canvas::draw(
    randar::Geometry& geometry,
    randar::TextureCollection& textures,
    randar::Transform& transform,
    randar::LightCollection& lights,
    randar::ShaderProgram& program)
{
    randar::DrawState state;
    state.textures = &textures;
    state.transform = &transform;
    state.lights = &lights;
    state.program = &program;

    this->draw(geometry, state);
}

void randar::Canvas::draw(randar::Geometry& geometry, randar::DrawState& state)
{
    static randar::Transform defaultTransform = randar::Transform();
    static randar::Skeleton defaultSkeleton = randar::Skeleton();
    static randar::TextureCollection defaultTextures = randar::TextureCollection();
    static randar::LightCollection defaultLights = randar::LightCollection();

    // Force the geometry onto the current context.
    this->framebuffer().ensureContext();
    if (!this->framebuffer().sameContext(geometry)) {
        geometry.initialize(this->framebuffer().context());
    }

    // Set state defaults.
    if (!state.transform) {
        state.transform = &defaultTransform;
    }
    Transform& transform = *state.transform;

    if (!state.skeleton) {
        state.skeleton = &defaultSkeleton;
    }
    Skeleton& skeleton = *state.skeleton;

    if (!state.textures) {
        state.textures = &defaultTextures;
    }
    TextureCollection& textures = *state.textures;

    if (!state.lights) {
        state.lights = &defaultLights;
    }
    LightCollection& lights = *state.lights;

    if (!state.program) {
        state.program = &this->framebuffer().context().defaultShaderProgram();
    }
    ShaderProgram& program = *state.program;

    // Ensure any new geometry data is synced.
    geometry.sync();

    // Fill basic shader program uniforms.
    program.uniform("projectionMatrix", this->camera().projectionMatrix());
    program.uniform("viewMatrix", this->camera().viewMatrix());
    program.uniform("modelMatrix", transform.transformMatrix());

    // Fill texture uniforms.
    uint16_t textureIndex = 0;

    if (lights.size() > 0) {
        // @todo - just using first light for now
        program.uniform("lightsEnabled", 1);

        program.uniform("lightMatrix0", lights[0]->matrix());

        lights[0]->map().active(textureIndex);
        program.uniform("lightmap0", textureIndex);
        textureIndex++;
    }

    else {
        program.uniform("lightsEnabled", 0);
    }

    std::string uniformName;
    for (uint32_t currentTextureIndex = 0; true; currentTextureIndex++) {
        uniformName = "geoTexture" + std::to_string(currentTextureIndex);
        if (!program.hasUniform(uniformName)) {
            break;
        }

        randar::Texture* currentTexture;
        if (currentTextureIndex < textures.size()) {
            currentTexture = textures[currentTextureIndex];
        } else {
            currentTexture = &randar::getDefaultTexture(
                this->framebuffer().context(), 2, 2, "rgba"
            );
        }

        currentTexture->active(textureIndex);
        program.uniform(uniformName, textureIndex);
        textureIndex++;
    }

    // Fill joint uniforms.
    if (skeleton.jointCount()) {
        std::vector<glm::mat4> jointMatrices;
        for (uint32_t i = 0; i < skeleton.jointCount(); i++) {
            jointMatrices.push_back(skeleton.matrix(i));
        }

        program.uniform("jointMatrices", jointMatrices);
    }

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

    // Reset bound textures.
    for (uint16_t i = 0; i < textureIndex; i++) {
        ::glActiveTexture(GL_TEXTURE0 + textureIndex);
        ::glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// Draws a model to the canvas.
void randar::Canvas::draw(randar::Model& model)
{
    static LightCollection lights;
    this->draw(model, lights);
}

void randar::Canvas::draw(randar::Model& model, randar::LightCollection& lights)
{
    if (!model.hasGeometry()) {
        return;
    }

    randar::DrawState state;
    state.transform = &model;
    state.lights    = &lights;

    if (model.hasSkeleton()) {
        state.skeleton = &model.skeleton();
    }

    if (model.hasShaderProgram()) {
        state.program = &model.shaderProgram();
    }

    this->draw(model.geometry(), state);
}

// Draws a world to the canvas.
void randar::Canvas::draw(randar::World& world, bool withLights)
{
    if (withLights) {
        for (auto light : world.lights) {
            light->generateMap(world);
        }
    }

    this->clear(world.backgroundColor);
    for (auto model : world.models) {
        if (withLights) {
            this->draw(*model, world.lights);
        } else {
            this->draw(*model);
        }
    }
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

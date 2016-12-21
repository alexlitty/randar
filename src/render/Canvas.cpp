#include <randar/render/Canvas.hpp>

randar::Canvas::~Canvas()
{

}

void randar::Canvas::clear(randar::Color color)
{
    ::glClearColor(color.r, color.g, color.b, color.a);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void randar::Canvas::bind() const
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ::glViewport(0, 0, 800, 600);
}

void randar::Canvas::draw(const randar::Drawable& drawable) const
{
    if (!this->shaderProgram) {
        throw std::runtime_error("Cannot draw without a shader program");
    }
    this->bind();

    glm::mat4 mvp = this->camera.getProjectionMatrix()
        * this->camera.getViewMatrix()
        * drawable.getTransformMatrix();

    ::glUseProgram(*this->shaderProgram);
    GLuint matrixId = ::glGetUniformLocation(*this->shaderProgram, "mvp");
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

    drawable.draw();
}

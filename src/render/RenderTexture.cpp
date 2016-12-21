#include <randar/render/RenderTexture.hpp>

randar::RenderTexture::RenderTexture()
{
    ::glGenFramebuffers(1, &this->framebuffer);
    this->bind();

    ::glGenTextures(1, &this->texture);
    ::glBindTexture(GL_TEXTURE_2D, this->texture);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    ::glGenRenderbuffers(1, &this->renderBuffer);
    ::glBindRenderbuffer(GL_RENDERBUFFER, this->renderBuffer);
    ::glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
    ::glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->renderBuffer);

    ::glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->texture, 0);

    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    ::glDrawBuffers(1, drawBuffers);

    if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Error while creating render texture");
    }
}

void randar::RenderTexture::bind() const
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
    ::glViewport(0, 0, 1024, 768);
}

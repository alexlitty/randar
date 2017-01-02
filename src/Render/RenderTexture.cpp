#include <randar/Render/RenderTexture.hpp>

randar::RenderTexture::RenderTexture()
{
    ::glGenFramebuffers(1, &this->framebuffer);
    this->bind();

    ::glGenTextures(1, &this->texture);
    ::glBindTexture(GL_TEXTURE_2D, this->texture);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 768, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    ::glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->texture, 0);

    ::glDrawBuffer(GL_NONE);

    if (::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Error while creating render texture: " + std::to_string(::glCheckFramebufferStatus(GL_FRAMEBUFFER)));
    }
}

randar::RenderTexture::~RenderTexture()
{
    ::glDeleteFramebuffers(1, &this->framebuffer);
    ::glDeleteTextures(1, &this->texture);
}

void randar::RenderTexture::bind() const
{
    ::glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
    ::glViewport(0, 0, 1024, 768);
}

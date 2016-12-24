#include <randar/engine/Repository.hpp>

// Retrieves an existing render texture.
randar::RenderTexture* randar::Repository::getRenderTexture(unsigned int id)
{
    randar::assertKey(this->renderTextures, id);
    return this->renderTextures[id];
}

// Primary repository instance.
randar::Repository randar::primaryRepository;

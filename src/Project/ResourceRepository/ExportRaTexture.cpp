#include <randar/Project/ResourceRepository.hpp>
#include <randar/Filesystem/BinaryFileWriter.hpp>

void randar::ResourceRepository::exportRaTexture(uint32_t textureId)
{
    Texture *texture = this->textures[textureId];

    if (!texture) {
        throw std::logic_error("Exporting nonexistent texture");
    }

    BinaryFileWriter stream(
        this->directory
            .getSubdirectory("textures")
            .getFile(std::to_string(textureId), "raTexture")
    );

    stream.write(texture->getType());
    stream.write(texture->getWidth());
    stream.write(texture->getHeight());

    for (auto value : texture->data) {
        stream.write(value);
    }

    // Fill missing data with opaque white.
    unsigned int requiredSize = texture->getWidth() * texture->getHeight() * 4;
    if (texture->data.size() < requiredSize) {
        for (unsigned int i = texture->data.size(); i < requiredSize; i++) {
            stream.write(255);
        }
    }   
}

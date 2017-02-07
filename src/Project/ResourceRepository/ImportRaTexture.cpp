#include <randar/Project/ResourceRepository.hpp>
#include <randar/Filesystem/BinaryFileReader.hpp>

void randar::ResourceRepository::importRaTexture(const randar::File& file)
{
    std::string basename = file.getBaseName();
    if (!randar::isInteger(basename)) {
        return;
    }

    BinaryFileReader stream(file);

    Texture *texture = new Texture(
        stream.read<std::string>(),
        stream.read<uint32_t>(),
        stream.read<uint32_t>()
    );

    try {
        uint32_t requiredSize = texture->getWidth() * texture->getHeight() * 4;

        for (uint32_t i = 0; i < requiredSize; i++) {
            texture->data.push_back(
                stream.read<uint8_t>()
            );
        }

        this->gpu.write(*texture);

        this->textures[std::stoi(basename)] = texture;
    }

    catch (...) {
        delete texture;
        throw std::runtime_error("Corrupt raTexture data");
    }
}

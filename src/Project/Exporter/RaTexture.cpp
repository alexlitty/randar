#include <randar/Project/Exporter.hpp>

void randar::Exporter::exportRaTexture(
    const randar::Texture& texture,
    const randar::File& file)
{
    BinaryFileWriter stream(file);

    stream.write(texture.getType());
    stream.write(texture.getWidth());
    stream.write(texture.getHeight());

    for (auto value : texture.data) {
        stream.write(value);
    }

    // Fill missing data with opaque white.
    unsigned int requiredSize = texture.getWidth() * texture.getHeight() * 4;
    if (texture.data.size() < requiredSize) {
        for (unsigned int i = texture.data.size(); i < requiredSize; i++) {
            stream.write(255);
        }
    }   
}

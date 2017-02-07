#include <pngpp/image.hpp>
#include <randar/Project/ResourceRepository.hpp>

void randar::ResourceRepository::importPng(const randar::File& file)
{
    // Load the PNG into memory.
    png::image<png::rgba_pixel> image(file);

    // Create a new randar texture.
    Texture *texture = new Texture(
        "rgba",
        image.get_width(),
        image.get_height(),
        false
    );

    // Read into randar texture, which starts with the bottom row.
    for (int32_t y = static_cast<int32_t>(texture->getHeight()) - 1; y >= 0; y--) {
        for (int32_t x = 0; x < static_cast<int32_t>(texture->getWidth()); x++) {
            png::rgba_pixel pixel = image.get_pixel(x, y);

            texture->data.push_back(pixel.red);
            texture->data.push_back(pixel.green);
            texture->data.push_back(pixel.blue);
            texture->data.push_back(pixel.alpha);
        }
    }

    this->addTexture(texture);
}

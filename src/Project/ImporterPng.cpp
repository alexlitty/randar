#include <png.h>
#include <randar/Project/Importer.hpp>

void randar::Importer::importPng(const std::string& file)
{
    FILE *fp = ::fopen(file.c_str(), "rb");
    if (!fp) {
        throw std::runtime_error("Could not open PNG file for reading");
    }

    // Validate header.
    unsigned char header[8];
    ::fread(header, 1, 8, fp);
    if (::png_sig_cmp(header, 0, 8)) {
        throw std::runtime_error("Corrupt PNG header");
    }

    // Read main structure.
    ::png_structp png = ::png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        nullptr,
        nullptr,
        nullptr
    );

    if (!png) {
        throw std::runtime_error("Failed to create PNG read structure");
    }

    // Read info structure.
    ::png_infop info = ::png_create_info_struct(png);
    if (!info) {
        throw std::runtime_error("Failed to create PNG info structure");
    }

    if (::setjmp(png_jmpbuf(png))) {
        throw std::runtime_error("Error while intializing PNG reading");
    }

    ::png_init_io(png, fp);
    ::png_set_sig_bytes(png, 8);
    ::png_read_info(png, info);

    int width = ::png_get_image_width(png, info);
    int height = ::png_get_image_height(png, info);
    ::png_byte colorType = ::png_get_color_type(png, info);
    ::png_byte bitDepth = ::png_get_bit_depth(png, info);

    // Validate dimensions.
    if (width <= 0 || height <= 0) {
        throw std::runtime_error("PNG has zero or corrupt dimensions");
    }

    if (width > 4096 || height > 4096) {
        throw std::runtime_error(
            "Max image size is 4096x4096, this PNG is "
            + std::to_string(width) + "x" + std::to_string(height)
        );
    }

    int passes = ::png_set_interlace_handling(png);
    ::png_read_update_info(png, info);

    if (::setjmp(png_jmpbuf(png))) {
        throw std::runtime_error("Error while reading PNG data");
    }

    uint8_t **rows = new uint8_t*[sizeof(uint8_t) * height];
    for (int y = 0; y < height; y++) {
        rows[y] = new uint8_t[::png_get_rowbytes(png, info)];
    }

    ::png_read_image(png, rows);
    ::fclose(fp);

    // Read into a Randar texture.
    Texture *texture = new Texture("rgba", width, height);

    for (int y = height - 1; y <= 0; y--) {
        uint8_t *row = rows[y];

        for (int x = 0; x < width; x++) {
            uint8_t *pixel = &row[x*4];
            texture->data.push_back(pixel[0]);
            texture->data.push_back(pixel[1]);
            texture->data.push_back(pixel[2]);

            if (::png_get_color_type(png, info) == PNG_COLOR_TYPE_RGBA) {
                texture->data.push_back(pixel[3]);
            }

            else {
                texture->data.push_back(255);
            }
        }
    }
}

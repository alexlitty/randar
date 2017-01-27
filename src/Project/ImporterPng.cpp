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

    int passes = ::png_set_interlace_handling(png);
    ::png_read_update_info(png, info);

    if (::setjmp(png_jmpbuf(png))) {
        throw std::runtime_error("Error while reading PNG data");
    }

    ::png_bytep *rows = new ::png_bytep[sizeof(::png_bytep) * height];
    for (int y = 0; y < height; y++) {
        rows[y] = new ::png_byte[::png_get_rowbytes(png, info)];
    }

    ::png_read_image(png, rows);
    ::fclose(fp);

    // Read into a Randar texture.
    Texture *texture = new Texture("rgba", width, height);

    for (int y = 0; y < height; y++) {
        unsigned char *row = rows[y];

        for (int x = 0; x < width; x++) {
            unsigned char *pixel = &row[x*4];
        }
    }
}

#include <randar/Render/Texture.hpp>

randar::Texture::Texture(
    ::GLuint initGlName,
    randar::Texture::Type initType,
    unsigned int initWidth,
    unsigned int initHeight
) :
  randar::GpuResource(initGlName),
  type(initType),
  width(initWidth),
  height(initHeight)
{

}

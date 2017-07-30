#ifndef RANDAR_RENDER_TEXTURE_COLLECTION_HPP
#define RANDAR_RENDER_TEXTURE_COLLECTION_HPP

#include <vector>
#include <randar/Render/Texture.hpp>

namespace randar
{
    typedef std::vector<randar::Texture*> TextureCollection;
}

#ifdef SWIG
    %template(TextureCollection) std::vector<randar::Texture*>;
#endif

#endif

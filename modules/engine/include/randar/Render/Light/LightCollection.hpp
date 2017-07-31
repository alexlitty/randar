#ifndef RANDAR_RENDER_LIGHT_LIGHT_COLLECTION_HPP
#define RANDAR_RENDER_LIGHT_LIGHT_COLLECTION_HPP

#include <vector>
#include <randar/Render/Light/BaseLight.hpp>

namespace randar
{
    typedef std::vector<randar::BaseLight*> LightCollection;
}

#ifdef SWIG
    %template(LightCollection) std::vector<randar::BaseLight*>;
#endif

#endif

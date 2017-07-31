#ifndef RANDAR_RENDER_MODEL_COLLECTION_HPP
#define RANDAR_RENDER_MODEL_COLLECTION_HPP

#include <vector>
#include <randar/Render/Model.hpp>

namespace randar
{
    typedef std::vector<randar::Model*> ModelCollection;
}

#ifdef SWIG
    %template(ModelCollection) std::vector<randar::Model*>;
#endif

#endif

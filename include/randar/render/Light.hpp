#ifndef RANDAR_RENDER_LIGHT_HPP
#define RANDAR_RENDER_LIGHT_HPP

#include <randar/render/RenderTexture.hpp>
#include <randar/engine/ResourceConsumer.hpp>
#include <randar/utility/File.hpp>

namespace randar
{
    class Light : virtual public ResourceConsumer
    {
    public:
        RenderTexture renderTexture;

        Light();
        void bind() const;
    };
}

#endif

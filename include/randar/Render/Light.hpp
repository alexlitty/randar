#ifndef RANDAR_RENDER_LIGHT_HPP
#define RANDAR_RENDER_LIGHT_HPP

#include <randar/Render/RenderTexture.hpp>
#include <randar/Engine/ResourceConsumer.hpp>
#include <randar/Utility/File.hpp>

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

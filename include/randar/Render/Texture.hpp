#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    class Texture : virtual public GpuResource
    {
    protected:
        /**
         * Type of texture.
         *
         * Valid values are "rgba" and "depth".
         */
        const std::string type;

        /**
         * Texture dimensions.
         */
        unsigned int width;
        unsigned int height;
    
    public:
        /**
         * Primary constructor.
         */
        Texture(
            std::string initType,
            unsigned int initWidth,
            unsigned int initHeight);

        /**
         * Construct from JSON.
         */
        Texture(const Json& json);

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize() override;
        virtual void destroy() override;

        /**
         * Checks the validity of this texture's information.
         *
         * Does not check GPU validity.
         *
         * If the texture is invalid, the error argument is filled with a
         * description of the problem. Otherwise the argument remains unchanged.
         */
        bool isValid(std::string& error) const;

        /**
         * Checks which kind of texture this is.
         */
        bool isRgba() const;
        bool isDepth() const;
 
        /**
         * Resizes this texture.
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * Retrieves the width and height of this texture.
         */
        unsigned int getWidth() const;
        unsigned int getHeight() const;

        /**
         * Converts this texture to a JSON representation.
         */
        virtual Json toJson() const override;
    };
}

#endif

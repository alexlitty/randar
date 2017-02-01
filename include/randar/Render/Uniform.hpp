#ifndef RANDAR_RENDER_UNIFORM_HPP
#define RANDAR_RENDER_UNIFORM_HPP

#include <randar/Engine/Glfw.hpp>
#include <randar/Engine/Resource.hpp>

namespace randar
{
    /**
     * A uniform on a shader program.
     */
    class Uniform : virtual public Resource
    {
        /**
         * Name of the uniform.
         */
        std::string name;

        /**
         * Location of the uniform on the program.
         *
         * -1 if the uniform is not used by the program.
         */
        ::GLint location;

    public:
        /**
         * Default constructor.
         *
         * Usually used when a certain uniform is required but is not
         * available. The uniform will have a location of -1 and will ignore
         * any data written to it.
         */
        Uniform();

        /**
         * Constructor.
         */
        Uniform(const std::string& initName, ::GLint initLocation = -1);

        /**
         * Copy constructor.
         */
        Uniform(const Uniform& other);

        /**
         * Move constructor.
         */
        Uniform(const Uniform&& other);

        /**
         * Gets the name of this uniform.
         */
        const std::string& getName() const;

        /**
         * Gets the location of this uniform on the program.
         */
        ::GLint getLocation() const;

        /**
         * Assignment operator.
         */
        Uniform& operator =(const Uniform& other);
    };
}

#endif

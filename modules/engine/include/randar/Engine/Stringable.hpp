#ifndef RANDAR_ENGINE_STRINGABLE_HPP
#define RANDAR_ENGINE_STRINGABLE_HPP

#include <iostream>
#include <string>

namespace randar
{
    /**
     * Base class for objects that can be converted to strings.
     */
    struct Stringable
    {
        /**
         * Main conversion method that should be implemented by children.
         *
         * By default, "<randar object>" is returned.
         */
        std::string toString() const;

        /**
         * Implicitly converts this object to a string.
         */
        operator std::string() const;
    };

    /**
     * Sends a stringable object to an output stream.
     */
    std::ostream& operator <<(std::ostream &os, const Stringable& object);
}

#endif

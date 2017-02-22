#ifndef RANDAR_MATH_RECT_HPP
#define RANDAR_MATH_RECT_HPP

#include <cef/include/internal/cef_types_wrappers.h>

namespace randar
{
    template <typename T>
    struct Rect
    {
        T left;
        T top;
        T width;
        T height;

        /**
         * Constructor.
         */
        Rect(T initLeft, T initTop, T initWidth, T initHeight)
        : left(initLeft),
          top(initTop),
          width(initWidth),
          height(initHeight)
        {

        }

        /**
         * Construct from a CEF rect.
         */
        Rect(const ::CefRect& rect)
        : left(rect.x),
          top(rect.y),
          width(rect.width),
          height(rect.height)
        {

        }
    };
}

#endif

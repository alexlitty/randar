#ifndef RANDAR_MATH_RECT_HPP
#define RANDAR_MATH_RECT_HPP

namespace randar
{
    template <typename T>
    struct Rect
    {
        T top;
        T left;
        T width;
        T height;

        Rect(T initTop, T initLeft, T initWidth, T initHeight)
        : top(initTop),
          left(initLeft),
          width(initWidth),
          height(initHeight)
        {

        }
    };
}

#endif

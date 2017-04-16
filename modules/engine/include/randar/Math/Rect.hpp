#ifndef RANDAR_MATH_RECT_HPP
#define RANDAR_MATH_RECT_HPP

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
         * Converts this rect to a string representation.
         */
        std::string toString() const
        {
            return "("
                + std::to_string(this->left) + ", " + std::to_string(this->top) + " ... "
                + std::to_string(this->width) + ", " + std::to_string(this->height) + ")";
        }

        operator std::string() const
        {
            return this->toString();
        }
    };
}

#endif

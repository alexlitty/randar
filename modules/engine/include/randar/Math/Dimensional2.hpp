#ifndef RANDAR_MATH_DIMENSIONAL2_HPP
#define RANDAR_MATH_DIMENSIONAL2_HPP

#include <limits>
#include <stdexcept>
#include <randar/Engine/Stringable.hpp>
#include <randar/Math/Vector2.hpp>

namespace randar
{
    /**
     * Base class for two-dimensional objects.
     */
    template <typename T>
    class Dimensional2 : virtual public Stringable
    {
    protected:
        T width;
        T height;

        T maxWidth;
        T maxHeight;

    public:
        /**
         * Disable assignments.
         */
        explicit Dimensional2(const Dimensional2<T>& other) = delete;
        Dimensional2<T>& operator =(const Dimensional2<T>& other) = delete;

        /**
         * Default constructor.
         *
         * Initializes the object with 0 width, 0 height, and no limits.
         */
        Dimensional2()
        : width(0),
          height(0)
        {

        }

        /**
         * Primary constructor.
         */
        Dimensional2(T initWidth, T initHeight)
        : width(initWidth),
          height(initHeight)
        {

        }

        /**
         * Whether this object has non-zero dimensions.
         */
        bool hasDimensions() const
        {
            return this->getWidth() != 0 && this->getHeight() != 0;
        }

    public:
        /**
         * Sets the width and height of this object.
         *
         * Invokes onResize after the new dimensions are set.
         */
        virtual void resize(T newWidth, T newHeight)
        {
            if (newWidth < 0 || newHeight < 0) {
                throw std::runtime_error("Dimensions must not be negative");
            }

            this->width = newWidth;
            this->height = newHeight;
        }

        /**
         * Sets the width or height of this object.
         *
         * Calls are delegated to the resize method. If you need to override the
         * resizing behavior, simply override resize.
         */
        void setWidth(T newWidth)
        {
            this->resize(newWidth, this->height);
        }

        void setHeight(T newHeight)
        {
            this->resize(this->width, newHeight);
        }

        /**
         * Gets the width and height of this object.
         */
        T getWidth() const
        {
            return this->width;
        }

        T getHeight() const
        {
            return this->height;
        }

        /**
         * Checks if a position is within this dimension's range.
         *
         * This check is 0-based. If the dimensions are 20x20, a position at
         * (5, 20) is out of range; (0, 19) is within range.
         */
        bool isWithinDimensions(const Vector2<T>& position)
        {
            return this->isWithinDimensions(position.x, position.y);
        }

        bool isWithinDimensions(T x, T y)
        {
            return x < this->getWidth()
                && y < this->getHeight()
                && x >= 0
                && y >= 0;
        }

        /**
         * Describes the dimensions of this object as a string.
         */
        virtual std::string toString() const
        {
            return std::to_string(this->width) + "x" + std::to_string(this->height);
        }
    };
}

#ifdef SWIG
    %template(Dimensional2_float) randar::Dimensional2<float>;

    %template(Dimensional2_int8) randar::Dimensional2<int8_t>;
    %template(Dimensional2_int16) randar::Dimensional2<int16_t>;
    %template(Dimensional2_int32) randar::Dimensional2<int32_t>;
    %template(Dimensional2_int64) randar::Dimensional2<int64_t>;

    %template(Dimensional2_uint8) randar::Dimensional2<uint8_t>;
    %template(Dimensional2_uint16) randar::Dimensional2<uint16_t>;
    %template(Dimensional2_uint32) randar::Dimensional2<uint32_t>;
    %template(Dimensional2_uint64) randar::Dimensional2<uint64_t>;
#endif

#endif

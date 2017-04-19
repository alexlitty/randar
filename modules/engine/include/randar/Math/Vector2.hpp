#ifndef RANDAR_MATH_VECTOR2_HPP
#define RANDAR_MATH_VECTOR2_HPP

namespace randar
{
    template <typename T>
    struct Vector2
    {
        T x;
        T y;

        /**
         * Default constructor.
         *
         * Initializes a (0, 0) vector.
         */
        Vector2()
        : x(0),
          y(0)
        {

        }

        /**
         * Primary constructor.
         */
        Vector2(T initX, T initY)
        : x(initX),
          y(initY)
        {

        }

        /**
         * Copy constructor.
         */
        Vector2(const Vector2<T>& other)
        {
            *this = other;
        }

        /**
         * Sets the values of this vector.
         */
        void set(T newX, T newY)
        {
            this->x = newX;
            this->y = newY;
        }

        /**
         * Sets the values of this vector to those of another vector.
         */
        void set(const Vector2<T>& other)
        {
            this->set(other.x, other.y);
        }

        /**
         * Assignment operator.
         */
        Vector2<T>& operator =(const Vector2<T>& other)
        {
            this->set(other);
            return *this;
        }
    };
}

#ifdef SWIG
    %template(Vector2_float) randar::Vector2<float>;

    %template(Vector2_int8) randar::Vector2<int8_t>;
    %template(Vector2_int16) randar::Vector2<int16_t>;
    %template(Vector2_int32) randar::Vector2<int32_t>;
    %template(Vector2_int64) randar::Vector2<int64_t>;

    %template(Vector2_uint8) randar::Vector2<uint8_t>;
    %template(Vector2_uint16) randar::Vector2<uint16_t>;
    %template(Vector2_uint32) randar::Vector2<uint32_t>;
    %template(Vector2_uint64) randar::Vector2<uint64_t>;
#endif

#endif

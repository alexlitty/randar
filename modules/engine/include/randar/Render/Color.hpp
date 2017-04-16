#ifndef RANDAR_RENDER_COLOR_HPP
#define RANDAR_RENDER_COLOR_HPP

#include <cstdint>

namespace randar
{
    /**
     * A color represented by red, green, blue, and alpha channels.
     *
     * The alpha channel represents complete transparency at value 0.
     *
     * Channels can be set and retrieved via 8-bit integers, but the
     * functionality is only provided for convenience. Don't use the integer
     * interfaces for core code.
     */
    class Color
    {
        /**
         * Internal data for this color.
         *
         * The four elements represent the red, green, blue, and alpha channels
         * respectively.
         *
         * Each value is ideally clamped within [0, 1].
         */
        float data[4];

    public:
        /**
         * Default constructor.
         *
         * Color is initialized to opaque black.
         */
        Color();

        /**
         * Primary constructor.
         *
         * Delegates to set, which safely initializes the color using floats.
         * Values are clamped within [0, 1].
         *
         * Alpha is optional and defaults to 1, fully opaque.
         *
         * No constructor is provided for blindly initializing the color values.
         * If performance is required, consider calling _set on an existing
         * instance or not using the class altogether.
         *
         * No constructor is provided for initializing the color using 8-bit
         * integers, for intuitive Node.js compatibility.
         *
         */
        Color(float rInit, float gInit, float bInit, float aInit = 1.0f);

        /**
         * Safely sets the color using float values.
         *
         * Values are clamped within [0, 1]. If all values are always clamped
         * beforehand, use _set.
         *
         * Alpha is optional and defaults to 1, fully opaque.
         */
        void set(float rNew, float gNew, float bNew, float aNew = 1.0f);

        /**
         * Blindly sets the color using float values.
         *
         * If any value is not clamped within [0, 1], behavior is undefined. If
         * any value may not be clamped beforehand, use set.
         *
         * Alpha is optional and defaults to 1, fully opaque.
         */
        inline void _set(float rNew, float gNew, float bNew, float aNew = 1.0f)
        {
            this->data[0] = rNew;
            this->data[1] = gNew;
            this->data[2] = bNew;
            this->data[3] = aNew;
        }

        /**
         * Safely sets a channel on the color using float values.
         *
         * Values are clamped within [0, 1].
         */
        void r(float v);
        void g(float v);
        void b(float v);
        void a(float v);

        /**
         * Blindly sets a channel on the color using float values.
         *
         * If a value is not clamped within [0, 1], behavior is undefined. If
         * any value may not be clamped beforehand, use the safe method
         * alternative.
         */
        inline void _r(float v) { this->data[0] = v; }
        inline void _g(float v) { this->data[1] = v; }
        inline void _b(float v) { this->data[2] = v; }
        inline void _a(float v) { this->data[3] = v; }

        /**
         * Sets the color using 8-bit integer values.
         *
         * Alpha is optional and defaults to 255, fully opaque.
         */
        void setInt(uint8_t rNew, uint8_t gNew, uint8_t bNew, uint8_t aNew = 255);

        /**
         * Sets a channel on the color using 8-bit integer values.
         */
        void rInt(uint8_t v);
        void gInt(uint8_t v);
        void bInt(uint8_t v);
        void aInt(uint8_t v);

        /**
         * Gets a channel on the color as a float clamped within [0, 1].
         */
        float r() const;
        float g() const;
        float b() const;
        float a() const;

        /**
         * Gets a channel on the color as an 8-bit integer.
         */
        uint8_t rInt() const;
        uint8_t gInt() const;
        uint8_t bInt() const;
        uint8_t aInt() const;

        /**
         * Randomizes the red, green, and blue channels in this color.
         *
         * If randomizeAlpha is true the alpha channel is also randomized,
         * otherwise it is left unaltered. By default randomizeAlpha is false.
         */
        void randomize(bool randomizeAlpha = false);
    };

    /**
     * Generates a random color with full opacity.
     */
    Color randomColor();
}

#endif

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
         * No constructor is provided for initializing the color using 8-bit
         * integers, for intuitive Node.js compatibility.
         *
         */
        Color(float rInit, float gInit, float bInit, float aInit = 1.0f);

        /**
         * Copy constructor.
         */
        Color(const Color& other);

        /**
         * Sets this color from another color.
         */
        void set(const Color& other);

        /**
         * Safely sets the color using float values.
         *
         * Alpha is optional and defaults to 1, fully opaque.
         */
        void set(float rNew, float gNew, float bNew, float aNew = 1.0f);

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

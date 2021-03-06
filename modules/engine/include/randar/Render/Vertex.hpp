#ifndef RANDAR_RENDER_VERTEX_HPP
#define RANDAR_RENDER_VERTEX_HPP

#include <cstdint>
#include <map>
#include <randar/Math/Vector3.hpp>
#include <randar/Render/Color.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Render/Joint.hpp>
#include <randar/Utility/Gl.hpp>

namespace randar
{
    struct Vertex
    {
        const unsigned int stride = 17;

        /**
         * Basic vertex information.
         */
        Vector3 position;
        Color color;
        Vector3 normal;

        /**
         * Texture information, where a textureId of -1 indicates no texture.
         */
        int8_t textureId = -1;
        Vector2<float> textureCoordinate;

        /**
         * The influencing joint indices, mapped against the influencing weight
         * per joint.
         *
         * Total joint weights must equal 255.
         */
        std::map<uint16_t, uint8_t> jointWeights;

        /**
         * Constructors.
         */
        Vertex(const Vector3& p = Vector3(), const Color& c = Color());
        Vertex(float x, float y, float z = 0.0f);
        Vertex(
            float x,
            float y,
            float z,
            float r,
            float g,
            float b,
            float a = 1.0f);

        /**
         * Copy constructor and assignment operator.
         */
        Vertex(const Vertex& other);
        Vertex& operator =(const Vertex& other);

        /**
         * Appends this vertex to an ongoing array.
         *
         * @@ deprecating
         */
        void appendTo(GLfloat* array) const;

        /**
         * Returns the vertex with a slight modification.
         *
         * Useful while writing programmatically generated shapes.
         */
        Vertex withPosition(const randar::Vector3& newPosition) const;
        Vertex withPosition(float x, float y, float z) const;

        Vertex withColor(const randar::Color& newColor) const;
        Vertex withNormal(const randar::Vector3& newNormal) const;

        Vertex withTextureId(int8_t newTextureId) const;
        Vertex withUV(const randar::Vector2<float>& newUv) const;
        Vertex withUV(float u, float v) const;

        Vertex withJoint(uint16_t jointIndex, uint8_t jointWeight = 255) const;
    };

    /**
     * Vertex comparison operator.
     */
    bool operator ==(const Vertex& a, const Vertex& b);

    /**
     * Node.js helpers for intuitive vertex creation.
     */
    Vertex vertex(const Vector3& p = Vector3(), const Color& c = Color());
    Vertex vertex(float x, float y, float z = 0.0f);
    Vertex vertex(
        float x,
        float y,
        float z,
        float r,
        float g,
        float b,
        float a = 1.0f
    );
}

#endif

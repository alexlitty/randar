#ifndef RANDAR_RENDER_VERTEX_HPP
#define RANDAR_RENDER_VERTEX_HPP

#include <cstdint>
#include <map>
#include <GL/glew.h>
#include <randar/Math/Vector3.hpp>
#include <randar/Render/Color.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Render/Joint.hpp>

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
        
        /**
         * Texture information, where a textureId of -1 indicates no texture.
         *
         * textureId is local to a mesh.
         */
        int8_t textureId = -1;
        Vector2<float> textureCoordinate;

        /**
         * The influencing joint indices, mapped against the influencing weight
         * per joint.
         *
         * Total joint weights must equal 255.
         */
        std::map<unsigned char, unsigned char> jointWeights;

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
         */
        void appendTo(GLfloat* array) const;
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

#ifndef RANDAR_RENDER_VERTEX_HPP
#define RANDAR_RENDER_VERTEX_HPP

#include <cstdint>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <randar/Math/Vector.hpp>
#include <randar/Render/Color.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Render/Joint.hpp>

namespace randar
{
    struct TextureCoordinate
    {
        float u;
        float v;
    };

    struct Vertex
    {
        const unsigned int stride = 17;

        /**
         * Basic vertex information.
         */
        Vector position;
        Color color;
        
        /**
         * Texture information, where a textureId of -1 indicates no texture.
         *
         * textureId is local to a mesh.
         */
        int8_t textureId;
        TextureCoordinate textureCoordinate;

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
        Vertex();
        Vertex(Vector initPosition, Color initColor);

        /**
         * Copy constructor.
         */
        Vertex(const Vertex& other);

        /**
         * Appends this vertex to an ongoing array.
         */
        void appendTo(GLfloat* array) const;

        /**
         * Assignment operator.
         */
        Vertex& operator =(const Vertex& other);
    };
}

#endif

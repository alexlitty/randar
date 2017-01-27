#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 4) in vec2 vertexTextureCoords;

uniform mat4 mvp;
uniform sampler2D textureSampler;

out vec4 fragmentColor;
out vec2 textureCoords;

void main()
{
    vec4 position = vec4(vertexPosition, 1);

    gl_Position = mvp * position;
    fragmentColor = fragmentColor;
    textureCoords = vertexTextureCoords;
}

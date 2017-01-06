#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec4 vertexJoints;
layout(location = 3) in vec4 vertexJointWeights;
layout(location = 4) in vec2 vertexTextureCoords;

uniform mat4 mvp;
uniform mat4 joints[80];
uniform sampler2D textureSampler;

out vec4 fragmentColor;
out vec2 textureCoords;

void main()
{
    vec4 position = vec4(vertexPosition, 1);

    gl_Position = mvp * position;
    fragmentColor = vec4(0, 1, 0, 1);
    textureCoords = vertexTextureCoords;
}

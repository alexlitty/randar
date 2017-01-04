#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec4 vertexJoints;
layout(location = 3) in vec4 vertexJointWeights;

uniform mat4 mvp;
uniform mat4 joints[80];

out vec4 fragmentColor;
out vec4 shadowCoord;

void main()
{
    vec4 position = vec4(vertexPosition, 1);

    gl_Position = mvp * position;
    fragmentColor = vertexColor;
    shadowCoord = gl_Position * mat4(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1
    ) * mvp;
}

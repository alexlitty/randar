#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

uniform mat4 mvp;

out vec4 fragmentColor;

void main()
{
    vec4 position = vec4(vertexPosition, 1);

    gl_Position = mvp * position;
    fragmentColor = fragmentColor;
}

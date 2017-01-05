#version 330 core
in vec4 fragmentColor;
in vec4 shadowCoord;
out vec4 color;

uniform sampler2D shadowMap;

void main() {
    float visibility = 0.0f;
    if (texture(shadowMap, shadowCoord.xy).z < shadowCoord.z) {
        visibility = 0.5f;
    }

    color = fragmentColor;
    //color = visibility * fragmentColor;
}

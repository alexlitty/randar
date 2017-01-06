#version 330 core
in vec4 fragmentColor;
in vec2 textureCoords;

out vec3 color;

uniform sampler2D textureSampler;

void main() {
    color = texture(textureSampler, textureCoords).rgb;
}

#version 330 core
in vec4 fragmentColor;
in vec2 textureCoords;

out vec4 color;

uniform sampler2D meshTexture0;

void main() {
    //color = vec4(texture(meshTexture0, textureCoords).rgb, 1);
    color = vec4(0.75, 0, 0.25, 1);
}

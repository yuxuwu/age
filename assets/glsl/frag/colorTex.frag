#version 330 core

in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {

    FragColor = mix(
        texture(texture1, vec2(TexCoord.x, 1-TexCoord.y)), 
        texture(texture2, vec2(TexCoord.x, 1-TexCoord.y)), 
        0.2);
}
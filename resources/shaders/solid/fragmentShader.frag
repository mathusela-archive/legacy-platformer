#version 330 core

in vec2 fTexCoord;

out vec4 FragColor;

uniform sampler2D diffusionMap; 

void main() {

    FragColor = texture(diffusionMap, fTexCoord);

}
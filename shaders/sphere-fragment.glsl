#version 330

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D CelestialBodyTexture;


void main() {
    FragColor = texture(CelestialBodyTexture, TexCoords);
}
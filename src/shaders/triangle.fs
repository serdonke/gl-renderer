#version 330 core

in vec3 trong;
out vec4 FragColor;

void main() {
    FragColor = vec4(trong, 1.0);
}

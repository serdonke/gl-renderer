#version 330 core
out vec4 FragColor;
in vec3 trong;
void main()
{
   FragColor = vec4(trong, 1.0);
};


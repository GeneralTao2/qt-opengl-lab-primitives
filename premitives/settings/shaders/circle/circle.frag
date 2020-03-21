#version 440 core
out vec4 FragColor;

in vec3 colorG;
uniform vec3 color;

void main()
{
    FragColor = vec4(colorG, 1.0);
}

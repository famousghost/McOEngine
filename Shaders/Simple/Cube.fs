#version 330 core

out vec4 fragColor;

in vec3 fs_color;

void main()
{
	fragColor = vec4(fs_color, 1.0f);
}
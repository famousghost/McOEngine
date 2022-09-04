#version 330 core

out vec4 fragColor;

uniform sampler2D Texture0;

in vec3 fs_color;
in vec2 fs_uv;

void main()
{
	vec3 col = texture(Texture0, fs_uv).rgb;
	fragColor = vec4(col, 1.0f);
}
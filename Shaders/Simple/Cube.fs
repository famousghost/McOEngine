#version 330 core

out vec4 fragColor;

uniform sampler2D Texture0;

in vec3 fs_color;
in vec2 fs_uv;
in vec3 fs_normal;
in vec4 fs_wpos;

const vec3 fs_lightPos = vec3(3.0f, 0.0f, 0.0f);

float diffuse(vec3 wpos, vec3 normal)
{
	vec3 lightDir = normalize(fs_lightPos - wpos);
	return clamp(dot(lightDir, normal), 0.0f, 1.0f);
}

void main()
{
	vec3 col = texture(Texture0, fs_uv).rgb;
	float diff = diffuse(fs_wpos.xyz, fs_normal);
	fragColor = vec4(col * diff, 1.0f);
}
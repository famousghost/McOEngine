#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 uv;

uniform mat4 MCOENGINE_MATRIX_M;
uniform mat4 MCOENGINE_MATRIX_V;
uniform mat4 MCOENGINE_MATRIX_P;

out vec3 fs_color;

void main()
{
	gl_Position = MCOENGINE_MATRIX_P * MCOENGINE_MATRIX_V * MCOENGINE_MATRIX_M * vec4(vertex, 1.0f);
	fs_color = color;
}
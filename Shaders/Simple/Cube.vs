#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 uv;

uniform mat4 MCOENGINE_MATRIX_M;
uniform mat4 MCOENGINE_MATRIX_V;
uniform mat4 MCOENGINE_MATRIX_P;

out vec3 fs_color;
out vec2 fs_uv;
out vec3 fs_normal;
out vec4 fs_wpos;

void main()
{
	fs_wpos = MCOENGINE_MATRIX_M * vec4(vertex, 1.0f); 
	gl_Position = MCOENGINE_MATRIX_P * MCOENGINE_MATRIX_V * fs_wpos;
	fs_normal = normalize(mat3(transpose(inverse(MCOENGINE_MATRIX_M))) * normal);
	fs_color = color;
	fs_uv = uv;
}
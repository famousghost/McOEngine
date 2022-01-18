#version 330 core
layout(location = 0) in vec3 vertex;

uniform mat4 MCOENGINE_MATRIX_M;
uniform mat4 MCOENGINE_MATRIX_V;
uniform mat4 MCOENGINE_MATRIX_P;

void main()
{
	gl_Position = MCOENGINE_MATRIX_P * MCOENGINE_MATRIX_V * MCOENGINE_MATRIX_M * vec4(vertex, 1.0f);
}
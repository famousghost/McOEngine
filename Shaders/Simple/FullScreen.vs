#version 330 core
layout(location = 0) in vec3 vertex;

uniform mat4 MCOENGINE_MATRIX_M;
uniform mat4 MCOENGINE_MATRIX_V;
uniform mat4 MCOENGINE_MATRIX_P;

out vec3 camWorldPos;
out vec3 camDirectionPos;

void main()
{
	gl_Position = MCOENGINE_MATRIX_P * MCOENGINE_MATRIX_V * MCOENGINE_MATRIX_M * vec4(vertex, 1.0f);
	
	camWorldPos = vec3(MCOENGINE_MATRIX_V[0][3], MCOENGINE_MATRIX_V[1][3], MCOENGINE_MATRIX_V[2][3]);
	camDirectionPos = vec3(MCOENGINE_MATRIX_V[2][0], MCOENGINE_MATRIX_V[2][1], MCOENGINE_MATRIX_V[2][2]);
}
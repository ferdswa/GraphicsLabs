#version 450 core

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec3 vCol;

out vec3 col;

void main()
{
	gl_Position=vPos;
	col = vCol;
}
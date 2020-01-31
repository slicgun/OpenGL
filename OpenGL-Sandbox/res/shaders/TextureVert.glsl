#version 460

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_texCoords;

out vec2 v_texCoords;

void main()
{
	v_texCoords = a_texCoords;
	gl_Position = vec4(a_position, 0.0, 1.0);
}
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec3 v_normal;
out vec3 v_fragPos;
out vec2 v_Texcoord;

void main()
{
	gl_Position = u_MVP * vec4(position, 1);
	v_fragPos = vec3(u_Model * vec4(position, 1));
	v_Texcoord = texcoord;
	v_normal = normal;
};
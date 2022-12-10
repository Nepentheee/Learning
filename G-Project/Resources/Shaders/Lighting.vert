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
	v_Texcoord = texcoord;
	v_fragPos = vec3(u_Model * vec4(position, 1.0));
//	v_normal = vec3(u_Model * vec4(normal, 0.0)); // 消除位移影响
	v_normal = mat3(transpose(inverse(u_Model))) * normal; // 法线矩阵

	gl_Position = u_MVP * vec4(position, 1);
};
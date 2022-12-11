#shader vertex
#version 330 core

layout(location = 0)in vec3 position;

out vec3 v_TextCoord;

uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	v_TextCoord = position;
	//v_TextCoord = vec3(position.x, -position.y, position.z);
	vec4 pos = u_Proj * u_View * vec4(position, 1);
	gl_Position = pos.xyww; // 强行把cubeMap的深度都改成1（透视除法会将 gl_Position.xyz / w）
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

in vec3 v_TextCoord;

uniform samplerCube skybox;

void main()
{
	color = texture(skybox, v_TextCoord);
};
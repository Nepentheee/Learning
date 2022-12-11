#shader vertex
#version 330 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 textCoord;

out vec2 v_TextCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1);
	v_TextCoord = textCoord;
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

in vec2 v_TextCoord;

uniform sampler2D Texture1;
uniform vec4 u_Color;

void main()
{
	color = texture(Texture1, v_TextCoord);
	color *= u_Color;
};
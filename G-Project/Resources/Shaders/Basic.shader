#shader vertex
#version 330 core

layout(location = 0)in vec2 position;
layout(location = 1)in vec2 textCoord;

out vec2 v_TextCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position.x, position.y, 0, 1);
	v_TextCoord = textCoord;
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	vec4 textColor = texture(Texture1, v_TextCoord);
	color = textColor;
};
#shader vertex
#version 330 core

layout(location = 0)in vec4 position;
layout(location = 1)in vec4 color;
layout(location = 2)in vec2 textCoord;
layout(location = 3)in int textIndex;

out vec4 v_Color;
out vec2 v_TextCoord;
flat out int v_TextIndex;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TextCoord = textCoord;
	v_TextIndex = textIndex;
	v_Color = color;
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

flat in int v_TextIndex;
in vec2 v_TextCoord;
in vec4 v_Color;

uniform vec4 u_Color;
uniform sampler2D textures[];

void main()
{
	if (v_TextIndex == 0)
		color = texture(textures[0], v_TextCoord);
	else
		color = texture(textures[1], v_TextCoord);

	//color = vec4(v_TextIndex, 1, 0, 1);
};
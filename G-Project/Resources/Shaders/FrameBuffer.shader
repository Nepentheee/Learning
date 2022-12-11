#shader vertex
#version 330 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 textCoord;

out vec2 v_TextCoord;

void main()
{
	gl_Position = vec4(position.xy, 0, 1);
	v_TextCoord = textCoord;
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

in vec2 v_TextCoord;

uniform sampler2D Texture1;

void main()
{
    color = texture(Texture1, v_TextCoord);

    // 反相
    color = vec4(vec3(1 - color), 1);

	// 灰度
	float average = (color.r + color.g + color.b) / 3.0;
	color = vec4(vec3(average), 1);

	// 卷积
    float offset = 1.0 / 300.0;
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset), // 左上
        vec2(0.0f, offset), // 正上
        vec2(offset, offset), // 右上
        vec2(-offset, 0.0f),   // 左
        vec2(0.0f, 0.0f),   // 中
        vec2(offset, 0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2(0.0f, -offset), // 正下
        vec2(offset, -offset)  // 右下
        );

    /*float kernel[9] = float[](
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
        );*/

    /*float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
        );*/

    float kernel[9] = float[](
       1,  1, 1,
       1, -8, 1,
       1,  1, 1
       );

    vec3 simpleTex[9];
    for (int i = 0; i < 9; i++)
    {
        simpleTex[i] = vec3(texture(Texture1, v_TextCoord.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += simpleTex[i] * kernel[i];

    color = vec4(col, 1.0);
};
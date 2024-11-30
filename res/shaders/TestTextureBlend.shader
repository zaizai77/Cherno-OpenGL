#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform float u_percent;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main()
{
	vec4 texColor = mix(texture(u_Texture0, v_TexCoord), texture(u_Texture1, v_TexCoord), u_percent);
	color = texColor;
};
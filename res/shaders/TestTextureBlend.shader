#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = position;
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
	vec4 texColor = mix(texture(u_Texture0, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.5);
	color = texColor;
};
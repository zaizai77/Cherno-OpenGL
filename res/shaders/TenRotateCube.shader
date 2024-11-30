#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main() {
	FragColor = mix(texture(u_Texture1, TexCoord), texture(u_Texture2, TexCoord), 0.2);
}
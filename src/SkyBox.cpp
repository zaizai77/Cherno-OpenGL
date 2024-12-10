#include "SkyBox.h"

#include <GL/glew.h>
#include <stb_image.h>
#include "VertexBufferLayout.h"

SkyBox::SkyBox(std::vector<std::string> faces, const std::string& shaderPath) : m_Shader(shaderPath) {
	m_CubemapTextureID = loadCubemap(faces);
	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_VAO->AddBuffer(*m_VBO, layout);
	m_Shader.Bind();
	m_Shader.SetUniform1i("skybox", 0);
}

SkyBox::~SkyBox() {

}

unsigned int SkyBox::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		stbi_set_flip_vertically_on_load(1); //将图片上下翻转
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void SkyBox::Bind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubemapTextureID);
}

void SkyBox::UnBind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyBox::SetShaderViewAndProj(glm::mat4& view, glm::mat4& proj) {
	m_Shader.Bind();
	m_Shader.SetUniformMat4f("view", view);
	m_Shader.SetUniformMat4f("projection", proj);
}

void SkyBox::DrawSkyBox() const {
	// change depth function so depth test passes when values are equal to depth buffer's content
	glDepthFunc(GL_LEQUAL);
	//设置观察和投影矩阵
	m_VAO->Bind();
	this->Bind();
	Render render;
	render.DrawArrays(*m_VAO, m_Shader);
	glDepthFunc(GL_LESS); // set depth function back to default
}
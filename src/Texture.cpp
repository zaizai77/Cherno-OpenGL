#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& path) 
	: m_RenderID(0), m_FilePath(path), m_LocationBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0) {

	stbi_set_flip_vertically_on_load(1); //将图片上下翻转
	m_LocationBuffer = stbi_load(path.c_str(), &m_Width,&m_Height,&m_BPP,4);

	GLCall(glGenTextures(1, &m_RenderID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	//设置图片缩小放大，嵌入的采样方式
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, m_LocationBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocationBuffer) {
		stbi_image_free(m_LocationBuffer);
	}
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_RenderID));
}

//slot 是想要绑定纹理的插槽
//一般电脑支持最大32个，手机支持8个，但是具体的还得具体看
void Texture::Bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::UnBind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
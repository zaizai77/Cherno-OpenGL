#pragma once

#include "Render.h"

class Texture {
private:
	unsigned int m_RenderID;
	std::string m_FilePath;
	unsigned char* m_LocationBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	//slot 是想要绑定纹理的插槽
	void Bind(unsigned int slot = 0) const;  
	void UnBind() const;
	 
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetRenderID() const { return m_RenderID; }
};
#pragma once

#include <iostream>
#include <vector>

#include "Render.h"
#include "Shader.h"
#include "VertexArray.h"

class SkyBox {
private:
	unsigned int m_CubemapTextureID;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    Shader m_Shader;
public:

	SkyBox(std::vector<std::string> faces,const std::string& shadrPath);
	~SkyBox();

	unsigned int loadCubemap(std::vector<std::string> faces);

    void SetShaderViewAndProj(glm::mat4& view, glm::mat4& proj);

    //直接将绘制也写在这里面，省事
    void DrawSkyBox() const;

    void Bind() const;
    void UnBind() const;

	inline unsigned int GetCubemapTextureID() const {
		return this->m_CubemapTextureID;
	}

};
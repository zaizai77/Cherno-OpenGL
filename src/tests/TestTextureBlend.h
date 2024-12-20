#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test {
	class TestTextureBlend : public Test {
	public:
		TestTextureBlend();
		~TestTextureBlend();

		virtual void OnUpdate(float delteTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture0;
		std::unique_ptr<Texture> m_Texture1;

		glm::mat4 m_Proj, m_View;
		glm::float32 m_TranslationA;
	};
}

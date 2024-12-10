#pragma once

#include "../Test.h"
#include "Camera.h"
#include "Texture.h"

#include <memory>

namespace test {
	class TestFrameBuffer : public Test {
	public:
		TestFrameBuffer();
		~TestFrameBuffer();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float delteTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

		GLFWwindow* m_window;

		std::unique_ptr<VertexArray> m_VAO0;
		std::unique_ptr<VertexArray> m_VAO1;
		std::unique_ptr<VertexArray> m_ScreenQuad_VAO;

		std::unique_ptr<IndexBuffer> m_IndexBuffer0;
		std::unique_ptr<VertexBuffer> m_VertexBuffer0;
		std::unique_ptr<IndexBuffer> m_IndexBuffer1;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		std::unique_ptr<VertexBuffer> m_ScreenQuad_VertexBuffer;

		std::unique_ptr<Shader> m_FramebufferShader;
		std::unique_ptr<Shader> m_FramebufferScreenShader;

		std::unique_ptr<Texture> m_Texture0;
		std::unique_ptr<Texture> m_Texture1;

		std::unique_ptr<FrameBuffer> m_FrameBuffer;
		unsigned int textureColorbuffer;
		unsigned int rbo;
		unsigned int framebuffer;
	};
}
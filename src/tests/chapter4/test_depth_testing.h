#pragma once

#include "../Test.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

#include <memory>

namespace test {
	class TestDepthTesting : public Test {
	public:
		TestDepthTesting();
		~TestDepthTesting();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float delteTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

		std::unique_ptr<Shader> m_ColorShader;

		GLFWwindow* m_window;

		std::unique_ptr<VertexArray> m_VAO0;
		std::unique_ptr<VertexArray> m_VAO1;
		std::unique_ptr<IndexBuffer> m_IndexBuffer0;
		std::unique_ptr<VertexBuffer> m_VertexBuffer0;
		std::unique_ptr<IndexBuffer> m_IndexBuffer1;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture0;
		std::unique_ptr<Texture> m_Texture1;
	};
}
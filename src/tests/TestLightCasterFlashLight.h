#pragma once
#include <Texture.h>

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

namespace test {
	class TestLightCasterFlashLight : public Test {
	public:
		TestLightCasterFlashLight();
		~TestLightCasterFlashLight();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float delteTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		GLFWwindow* m_Window;

		// lighting
		glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

		//shader
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_ColorShader;
		std::unique_ptr<Shader> m_CubeShader;
		std::unique_ptr<Texture> m_Texture0;
		std::unique_ptr<Texture> m_Texture1;
	};
}
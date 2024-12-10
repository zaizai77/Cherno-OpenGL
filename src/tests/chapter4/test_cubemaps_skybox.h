#pragma once

#include "../Test.h"
#include "Texture.h"
#include "SkyBox.h"

#include <memory>

namespace test {
	class TestCubemapsSkybox : public Test{
	public:
		TestCubemapsSkybox();
		~TestCubemapsSkybox();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float delteTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		std::unique_ptr<SkyBox> m_SkyBox;
		std::unique_ptr<Shader> m_CubeShader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Texture;

		GLFWwindow* m_window;
	};
}
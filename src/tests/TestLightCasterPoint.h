#pragma once

#include <Texture.h>

#include "Test.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

namespace test {
	class TestLightCasterPoint : public Test {
	public:
		TestLightCasterPoint();
		~TestLightCasterPoint();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float delteTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		void processInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				camera.ProcessKeyboard(FORWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				camera.ProcessKeyboard(BACKWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				camera.ProcessKeyboard(LEFT, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				camera.ProcessKeyboard(RIGHT, deltaTime);
		}

	private:
		Camera camera;
		GLFWwindow* m_Window;

		//camera
		float lastX = test::SCR_WIDTH / 2.0f;
		float lastY = test::SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		//timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

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
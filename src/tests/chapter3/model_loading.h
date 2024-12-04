#pragma once

#include "../Test.h"
#include "Camera.h"
#include "Model.h"

#include <memory>

namespace test {
	class ModelLoading : public Test {
	public:
		ModelLoading();
		~ModelLoading();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float delteTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

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

	private :
		Camera camera;

		float lastX = SCR_WIDTH / 2.0f;
		float lastY = SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		// timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		std::unique_ptr<Shader> m_ColorShader;

		Model ourModel;

		GLFWwindow* m_window;
	};
}
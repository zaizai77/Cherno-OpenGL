#pragma once
#include <functional>
#include <iostream>
#include <vector>

#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace test {

	const unsigned int SCR_WIDTH = 960;
	const unsigned int SCR_HEIGHT = 720;

	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnStart(GLFWwindow* window) {}
		virtual void OnUpdate(float delteTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

		void processInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				camera.ProcessKeyboard(FORWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				camera.ProcessKeyboard(BACKWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				camera.ProcessKeyboard(LEFT, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				camera.ProcessKeyboard(RIGHT, deltaTime);

			//std::cout << "processInput" << std::endl;
		}

		float lastX = SCR_WIDTH / 2.0f;
		float lastY = SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		// timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}

		void OnImGuiRender() override;
	private:
		Test*& m_CurrentTest;  //当前应用中活动的
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}
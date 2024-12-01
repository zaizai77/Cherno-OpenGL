#pragma once
#include <functional>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnStart(GLFWwindow* window) {}
		virtual void OnUpdate(float delteTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void ProcessInput(GLFWwindow* window) {}
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
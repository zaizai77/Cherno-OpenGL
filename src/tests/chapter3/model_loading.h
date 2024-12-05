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

	private :
		std::unique_ptr<Shader> m_ColorShader;

		Model ourModel;

		GLFWwindow* m_window;
	};
}
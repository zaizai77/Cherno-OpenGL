#include "model_loading.h"

#include "Render.h"
#include "imgui/imgui.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace test {
	ModelLoading::ModelLoading() 
		: camera(glm::vec3(0.0f, 0.0f, 3.0f)), ourModel("res/model/nanosuit/nanosuit.obj") 
	{
		m_ColorShader = std::make_unique<Shader>("res/shaders/chapter3/model_loading.shader");
		
	}
	ModelLoading::~ModelLoading(){

	}

	void ModelLoading::OnStart(GLFWwindow* window) {
		m_window = window;
		glEnable(GL_DEPTH_TEST);
	}

	void ModelLoading::OnUpdate(float delteTime) {
		
	}

	void ModelLoading::OnRender() {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(m_window);

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_ColorShader->Bind();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		m_ColorShader->SetUniformMat4f("projection", projection);
		m_ColorShader->SetUniformMat4f("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		m_ColorShader->SetUniformMat4f("model", model);
		ourModel.Draw(*m_ColorShader);
	}

	void ModelLoading::OnImGuiRender() {

	}
}
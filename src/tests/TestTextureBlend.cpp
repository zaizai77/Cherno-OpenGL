#include "TestTextureBlend.h"

#include "Render.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace test {
	TestTextureBlend::TestTextureBlend() 
		: m_Proj(glm::ortho(0.0f,600.0f,0.0f,500.0f,-1.0f,1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(0.5f)
	{
		float positions[] = {
			100.0f, 100.0f, 0.0f, 0.0f,  // 0
			200.0f, 100.0f, 1.0f, 0.0f,  // 1
			200.0f, 200.0f, 1.0f, 1.0f,  // 2
			100.0f, 200.0f, 0.0f, 1.0f   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, static_cast<unsigned long long>(4) * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/TestTextureBlend.shader"); 
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
		m_Shader->SetUniform1i("u_Texture", 0);
		m_Shader->SetUniform1i("u_Texture1", 1);

		m_Texture0 = std::make_unique<Texture>("res/textures/14fnm.png");
		m_Texture1 = std::make_unique<Texture>("res/textures/smileface.png");
	}

	TestTextureBlend::~TestTextureBlend() {

	}

	void TestTextureBlend::OnUpdate(float delteTime) {

	}

	void TestTextureBlend::OnRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		constexpr Render renderer;

		m_Texture0->Bind(0);
		m_Texture1->Bind(1);

		{
			glm::mat4 model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));
			//转到屏幕外面去了
			//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

			//不知道哪里写错了，画不出来
			//m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -3.0f));
			//float screenWidth = 600.0f, screenHeight = 500.0f;
			//m_Proj = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);

			const glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->SetUniform1f("u_percent", m_TranslationA);

			GLCall(renderer.DrawElements(*m_VAO, *m_IndexBuffer, *m_Shader));
		}
	}

	void TestTextureBlend::OnImGuiRender() {
		ImGui::SliderFloat("m_TranslationA", &m_TranslationA, 0.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", static_cast<double>(1000.0f / ImGui::GetIO().Framerate),
			static_cast<double>(ImGui::GetIO().Framerate));
	}
}
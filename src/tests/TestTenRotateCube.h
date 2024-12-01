#pragma once
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test {
	class TestTenRotateCube : public Test {
	public:
		TestTenRotateCube();
		~TestTenRotateCube();

		void OnStart(GLFWwindow* window) override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void ProcessInput(GLFWwindow* window) override;

		void mouse_callback_fun(GLFWwindow* window, double xposIn, double yposIn);
		void scroll_callback_fun(GLFWwindow* window, double xoffset, double yoffset);

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture0;
		std::unique_ptr<Texture> m_Texture1;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;

		GLFWwindow* m_Window;

		//摄像机移动相关
		bool firstMouse = true;
		float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		float pitch = 0.0f;
		float lastX = 800.0f / 2.0;
		float lastY = 600.0 / 2.0;
		float fov = 45.0f;

		const unsigned int SCR_WIDTH = 960;
		const unsigned int SCR_HEIGHT = 720;

		// timing
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

	public:
		
	};
}
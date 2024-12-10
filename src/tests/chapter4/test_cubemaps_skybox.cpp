#include "test_cubemaps_skybox.h"

#include "Render.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

namespace test {

    void TestCubemapsSkybox_mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    void TestCubemapsSkybox_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	TestCubemapsSkybox::TestCubemapsSkybox() {
        float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        m_VAO = std::make_unique<VertexArray>();

        m_VBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
        VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(3);
        cubeLayout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, cubeLayout);

        std::vector<std::string> faces
        {
            "res/skybox/skyboxblue/right.jpg",
            "res/skybox/skyboxblue/left.jpg",
            "res/skybox/skyboxblue/top.jpg",
            "res/skybox/skyboxblue/bottom.jpg",
            "res/skybox/skyboxblue/front.jpg",
            "res/skybox/skyboxblue/back.jpg"
        };

        m_Texture = std::make_unique<Texture>("res/textures/container.jpg");
        m_Texture->Bind(0);

        m_SkyBox = std::make_unique<SkyBox>(faces, "res/shaders/chapter4/skybox.shader");
        m_CubeShader = std::make_unique<Shader>("res/shaders/chapter4/cubemaps.shader");
        m_CubeShader->Bind();
        m_CubeShader->SetUniform1i("texture1", 0);

        glEnable(GL_DEPTH_TEST);
	}

	TestCubemapsSkybox::~TestCubemapsSkybox() {

	}

	void TestCubemapsSkybox::OnStart(GLFWwindow* window) {
        m_window = window;

        glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));

        glfwSetCursorPosCallback(m_window, test::TestCubemapsSkybox_mouse_callback);
        glfwSetScrollCallback(m_window, test::TestCubemapsSkybox_scroll_callback);

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
	}
	void TestCubemapsSkybox::OnUpdate(float delteTime) {

	}

	void TestCubemapsSkybox::OnRender() {

        Render render;

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(m_window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_CubeShader->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_CubeShader->SetUniformMat4f("model", model);
        m_CubeShader->SetUniformMat4f("view", view);
        m_CubeShader->SetUniformMat4f("projection", projection);

        render.DrawArrays(*m_VAO, *m_CubeShader);

        // draw skybox as last
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        m_SkyBox->SetShaderViewAndProj(view, projection);
        m_SkyBox->DrawSkyBox();
	}

	void TestCubemapsSkybox::OnImGuiRender() {

	}

    void TestCubemapsSkybox::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    void TestCubemapsSkybox::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }

    void TestCubemapsSkybox_mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
        TestCubemapsSkybox* light = reinterpret_cast<TestCubemapsSkybox*>(glfwGetWindowUserPointer(window));
        light->mouse_callback(window, xposIn, yposIn);
    }

    void TestCubemapsSkybox_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        TestCubemapsSkybox* light = reinterpret_cast<TestCubemapsSkybox*>(glfwGetWindowUserPointer(window));
        light->mouse_callback(window, xoffset, yoffset);
    }
}
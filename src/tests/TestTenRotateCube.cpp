#include "TestTenRotateCube.h"

#include "Render.h"
#include "imgui/imgui.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>


namespace test {
	TestTenRotateCube::TestTenRotateCube() {
        float vertices[] = {
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

        unsigned int indices[] = {
            0,1,2,
            3,4,5,
            6,7,8,
            9,10,11,
            12,13,14,
            15,16,17,
            18,19,20,
            21,22,23,
            24,25,26,
            27,28,29,
            30,31,32,
            33,34,35
        };

        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);
        
        m_Shader = std::make_unique<Shader>("res/shaders/TenRotateCube.shader");
        m_Shader->Bind();
        m_Shader->SetUniform1i("u_Texture1", 0);
        m_Shader->SetUniform1i("u_Texture2", 1);

        m_Texture0 = std::make_unique<Texture>("res/textures/14fnm.png");
        m_Texture1 = std::make_unique<Texture>("res/textures/smileface.png");
	}

	TestTenRotateCube::~TestTenRotateCube() {

	}

	void TestTenRotateCube::OnUpdate(float deltaTime) {

	}

	void TestTenRotateCube::OnRender() {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        constexpr Render render;

        m_Texture0->Bind(0);
        m_Texture1->Bind(1);

        //不同的摄像机方案，用哪一个将哪一个展开
#pragma region //自动旋转摄像机

        {
           // //glm::mat4 model = glm::mat4(1.0f);
           //// glm::mat4 view = glm::mat4(1.0f);
           // glm::mat4 projection = glm::mat4(1.0f);

           // //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 1.0f));
           // //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
           // projection = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);

           // m_Shader->Bind();
           // //m_Shader->SetUniformMat4f("model", model);
           // //m_Shader->SetUniformMat4f("view", view);
           // m_Shader->SetUniformMat4f("projection", projection);

           // for (unsigned int i = 0; i < 10; i++)
           // {
           //     float radius = 10.0f;
           //     float camX = sin(glfwGetTime()) * radius;
           //     float camZ = cos(glfwGetTime()) * radius;
           //     glm::mat4 view;
           //     view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
           //     glm::mat4 model = glm::mat4(1.0f);
           //     model = glm::translate(model, cubePositions[i]);
           //     float angle = 20.0f * glfwGetTime();
           //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
           //     m_Shader->SetUniformMat4f("model", model);
           //     m_Shader->SetUniformMat4f("view", view);

           //     GLCall(render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader));
           // }
           // //GLCall(render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader));
            
        }
#pragma endregion

#pragma region //键盘控制移动摄像机

        {
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("projection", projection);

            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 view;
                view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * glfwGetTime();
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                m_Shader->SetUniformMat4f("model", model);
                m_Shader->SetUniformMat4f("view", view);

                GLCall(render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader));
            }

        }
#pragma endregion

	}

    void TestTenRotateCube::ProcessInput(GLFWwindow* window) {
        float cameraSpeed = 0.005f; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

	void TestTenRotateCube::OnImGuiRender() {
        ImGui::SliderFloat3("cameraPos", &cameraPos.x, 0.0f, 100.0f);
        ImGui::SliderFloat3("cameraFront", &cameraFront.x, -1.0f, 100.0f);
        ImGui::SliderFloat3("cameraUp", &cameraUp.x, 0.0f, 100.0f);
	}
}
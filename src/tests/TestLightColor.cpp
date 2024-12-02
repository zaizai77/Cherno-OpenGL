#include "TestLightColor.h"

#include "Render.h"
#include "imgui/imgui.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace test {

    void TestLightColor_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void TestLightColor_mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

	TestLightColor::TestLightColor() : camera(glm::vec3(0.0f,0.0f,6.0f)) {
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();
        
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);

        m_ColorShader = std::make_unique<Shader>("res/shaders/LightColor.shader"); 
        m_CubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

        m_ColorShader->Bind();
        m_CubeShader->Bind();
	}

	TestLightColor::~TestLightColor() {

	}

    void TestLightColor::OnStart(GLFWwindow* window) {
        glEnable(GL_DEPTH_TEST);
        m_Window = window;

        glfwSetWindowUserPointer(m_Window, reinterpret_cast<void*>(this));

        glfwSetCursorPosCallback(m_Window, test::TestLightColor_mouse_callback);
        glfwSetScrollCallback(m_Window, test::TestLightColor_scroll_callback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

	void TestLightColor::OnUpdate(float delteTime) {

	}

	void TestLightColor::OnRender() {
        processInput(m_Window);
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        constexpr Render render;

        //processInput(m_Window);

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        GLCall(m_ColorShader->Bind());

        GLCall(m_ColorShader->SetUniform3f("light.ambient", ambientColor));
        GLCall(m_ColorShader->SetUniform3f("light.diffuse", diffuseColor));
        GLCall(m_ColorShader->SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);)

        GLCall(m_ColorShader->SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f));
        GLCall(m_ColorShader->SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f));
        GLCall(m_ColorShader->SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f));
        GLCall(m_ColorShader->SetUniform1f("material.shininess", 32.0f));

        //glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4  projection = glm::perspective(glm::radians(camera.Zoom),
            (float)test::SCR_WIDTH / (float)test::SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        GLCall(m_ColorShader->SetUniformMat4f("projection", projection));
        GLCall(m_ColorShader->SetUniformMat4f("view", view));

        //change lightPos
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

        glm::mat4 model = glm::mat4(1.0f);
        GLCall(m_ColorShader->SetUniformMat4f("model", model));
        GLCall(m_ColorShader->SetUniform3f("lightPos", lightPos));
        GLCall(m_ColorShader->SetUniform3f("viewPos", camera.Position));

        GLCall(m_VAO->Bind());
        GLCall(render.Draw(*m_VAO, *m_IndexBuffer, *m_ColorShader));

        GLCall(m_VAO->Bind());
        GLCall(m_CubeShader->Bind());
        GLCall(m_CubeShader->SetUniformMat4f("projection", projection));
        GLCall(m_CubeShader->SetUniformMat4f("view", view));
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        m_CubeShader->SetUniformMat4f("model", model);
        GLCall(render.Draw(*m_VAO, *m_IndexBuffer, *m_CubeShader));
        
	}

	void TestLightColor::OnImGuiRender() {
	
	}

    void TestLightColor::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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

    void TestLightColor::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }

    void TestLightColor_mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
        TestLightColor* light = reinterpret_cast<TestLightColor*>(glfwGetWindowUserPointer(window));
        light->mouse_callback(window, xposIn, yposIn);
    }

    void TestLightColor_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        TestLightColor* light = reinterpret_cast<TestLightColor*>(glfwGetWindowUserPointer(window));
        light->mouse_callback(window, xoffset, yoffset);
    }

}
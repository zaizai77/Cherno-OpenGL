#include "TestLightCasterFlashLight.h"

#include "Render.h"
#include "imgui/imgui.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace test {

    void TestLightCasterFlashLight_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void TestLightCasterFlashLight_mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

    TestLightCasterFlashLight::TestLightCasterFlashLight() : camera(glm::vec3(0.0f, 0.0f, 6.0f)) {
        float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);

        m_ColorShader = std::make_unique<Shader>("res/shaders/LightCasterFlashLight.shader");
        m_CubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

        m_Texture0 = std::make_unique<Texture>("res/textures/container2.png");
        m_Texture1 = std::make_unique<Texture>("res/textures/container2_specular.png");
        m_Texture0->Bind(0);
        m_Texture1->Bind(1);

        m_ColorShader->Bind();
        m_CubeShader->Bind();
    }

    TestLightCasterFlashLight::~TestLightCasterFlashLight() {

    }

    void TestLightCasterFlashLight::OnStart(GLFWwindow* window) {
        glEnable(GL_DEPTH_TEST);
        m_Window = window;

        glfwSetWindowUserPointer(m_Window, reinterpret_cast<void*>(this));

        glfwSetCursorPosCallback(m_Window, test::TestLightCasterFlashLight_mouse_callback);
        glfwSetScrollCallback(m_Window, test::TestLightCasterFlashLight_scroll_callback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void TestLightCasterFlashLight::OnUpdate(float delteTime) {

    }

    void TestLightCasterFlashLight::OnRender() {

        // positions all containers
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

        processInput(m_Window);
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        constexpr Render render;

        //processInput(m_Window);

        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLCall(m_ColorShader->Bind());

        GLCall(m_ColorShader->SetUniform3f("light.position", camera.Position));
        GLCall(m_ColorShader->SetUniform3f("light.direction", camera.Front));
        GLCall(m_ColorShader->SetUniform1f("light.cutOff", glm::cos(glm::radians(12.5f))));
        GLCall(m_ColorShader->SetUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f))));

        GLCall(m_ColorShader->SetUniform1f("light.constant", 1.0f));
        GLCall(m_ColorShader->SetUniform1f("light.linear", 0.09f));
        GLCall(m_ColorShader->SetUniform1f("light.quadratic", 0.032f));

        GLCall(m_ColorShader->SetUniform1i("material.diffuse", 0));
        GLCall(m_ColorShader->SetUniform1i("material.specular", 1));
        GLCall(m_ColorShader->SetUniform1f("material.shininess", 32.0f));

        GLCall(m_ColorShader->SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f));
        GLCall(m_ColorShader->SetUniform3f("light.diffuse", 0.7f, 0.7f, 0.7f));
        GLCall(m_ColorShader->SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);)


            //glm::mat4 projection = glm::mat4(1.0f);
            glm::mat4  projection = glm::perspective(glm::radians(camera.Zoom),
                (float)test::SCR_WIDTH / (float)test::SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        GLCall(m_ColorShader->SetUniformMat4f("projection", projection));
        GLCall(m_ColorShader->SetUniformMat4f("view", view));


        glm::mat4 model = glm::mat4(1.0f);

        // GLCall(m_ColorShader->SetUniformMat4f("model", model));
        GLCall(m_ColorShader->SetUniform3f("viewPos", camera.Position));

        GLCall(m_VAO->Bind());

        //m_ColorShader->SetUniform3f("light.direction", -0.2f, -1.0f, -0.3f);

        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_ColorShader->SetUniformMat4f("model", model);
            GLCall(render.Draw(*m_VAO, *m_IndexBuffer, *m_ColorShader));
        }

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

    void TestLightCasterFlashLight::OnImGuiRender() {

    }

    void TestLightCasterFlashLight::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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

    void TestLightCasterFlashLight::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }

    void TestLightCasterFlashLight_mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
        TestLightCasterFlashLight* light = reinterpret_cast<TestLightCasterFlashLight*>(glfwGetWindowUserPointer(window));
        light->mouse_callback(window, xposIn, yposIn);
    }

    void TestLightCasterFlashLight_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        TestLightCasterFlashLight* light = reinterpret_cast<TestLightCasterFlashLight*>(glfwGetWindowUserPointer(window));
        light->mouse_callback(window, xoffset, yoffset);
    }

}
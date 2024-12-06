#include "test_stencil_testing.h"

#include "Render.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace test {
    TestStencilTesting::TestStencilTesting() {
        m_ColorShader = std::make_unique<Shader>("res/shaders/chapter4/stencil_testing.shader");
        m_SingleShader = std::make_unique<Shader>("res/shaders/chapter4/stencil_single.shader");

    }
    TestStencilTesting::~TestStencilTesting() {}

    void TestStencilTesting::OnStart(GLFWwindow* window) {
        m_window = window;

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

        float planeVertices[] = {
            // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        };

        unsigned int cubeIndices[] = {
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

        unsigned int planeIndices[] = {
            0,1,2,
            3,4,5
        };

        m_Texture0 = std::make_unique<Texture>("res/textures/marble.jpg");
        m_Texture1 = std::make_unique<Texture>("res/textures/metal.png");

        m_Texture0->Bind(0);
        m_Texture1->Bind(1);

        m_ColorShader = std::make_unique<Shader>("res/shaders/chapter4/depth_testing.shader");

        m_VAO0 = std::make_unique<VertexArray>();

        m_VertexBuffer0 = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
        VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(3);
        cubeLayout.Push<float>(2);
        m_VAO0->AddBuffer(*m_VertexBuffer0, cubeLayout);
        m_IndexBuffer0 = std::make_unique<IndexBuffer>(cubeIndices, 36);

        m_VAO1 = std::make_unique<VertexArray>();
        m_VertexBuffer1 = std::make_unique<VertexBuffer>(planeVertices, sizeof(planeVertices));
        VertexBufferLayout planeLayout;
        planeLayout.Push<float>(3);
        planeLayout.Push<float>(2);
        m_VAO1->AddBuffer(*m_VertexBuffer1, planeLayout);
        m_IndexBuffer1 = std::make_unique<IndexBuffer>(planeIndices, 6);

        m_ColorShader->Bind();

        m_ColorShader->SetUniform1i("texture1", 0);
    }

    void TestStencilTesting::OnUpdate(float delteTime) {

    }

    void TestStencilTesting::OnRender() {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        GLCall(processInput(m_window));

        Render render;

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

        m_SingleShader->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_SingleShader->SetUniformMat4f("view", view);
        m_SingleShader->SetUniformMat4f("projection", projection);

        m_ColorShader->Bind();
        m_ColorShader->SetUniformMat4f("view", view);
        m_ColorShader->SetUniformMat4f("projection", projection);

        glStencilMask(0x00);
        //floor 
        m_ColorShader->SetUniform1i("texture1", 1);
        m_ColorShader->SetUniformMat4f("model", glm::mat4(1.0f));
        render.DrawElements(*m_VAO1, *m_IndexBuffer1, *m_ColorShader);

        // 1st. render pass, draw objects as normal, writing to the stencil buffer
        // --------------------------------------------------------------------
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        //cubes
        m_ColorShader->SetUniform1i("texture1", 0);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_ColorShader->SetUniformMat4f("model", model);
        render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_ColorShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        m_ColorShader->SetUniformMat4f("model", model);
        render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_ColorShader);

        // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
        // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing 
        // the objects' size differences, making it look like borders.
        // -----------------------------------------------------------------------------------------------------------------------
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        m_SingleShader->Bind();
        
        float scale = 1.1f;

        //cubes
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        m_SingleShader->SetUniformMat4f("model", model);
        render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_SingleShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        m_SingleShader->SetUniformMat4f("model", model);
        render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_SingleShader);
    
    }

    void TestStencilTesting::OnImGuiRender() {

    }
}
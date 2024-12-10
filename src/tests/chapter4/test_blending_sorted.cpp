#include "test_blending_sorted.h"

#include "Render.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <map>

namespace test {
    TestBlendingSorted::TestBlendingSorted() {
        m_ColorShader = std::make_unique<Shader>("res/shaders/chapter4/depth_testing.shader");
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    TestBlendingSorted::~TestBlendingSorted() {}

    void TestBlendingSorted::OnStart(GLFWwindow* window) {
        m_window = window;

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

        float transparentVertices[] = {
            // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
            0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
            1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
            1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
            1.0f,  0.5f,  0.0f,  1.0f,  0.0f
        };

        m_Texture0 = std::make_unique<Texture>("res/textures/marble.jpg");
        m_Texture1 = std::make_unique<Texture>("res/textures/metal.png");
        m_Texture2 = std::make_unique<Texture>("res/textures/blending_transparent_window.png");

        m_Texture0->Bind(0);
        m_Texture1->Bind(1);
        m_Texture2->Bind(2);

        m_ColorShader = std::make_unique<Shader>("res/shaders/chapter4/blending_test.shader");

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

        m_VAO2 = std::make_unique<VertexArray>();
        m_VertexBuffer2 = std::make_unique<VertexBuffer>(transparentVertices, sizeof(transparentVertices));
        VertexBufferLayout grassLayout;
        grassLayout.Push<float>(3);
        grassLayout.Push<float>(2);
        m_VAO2->AddBuffer(*m_VertexBuffer2, grassLayout);

        m_ColorShader->Bind();

        m_ColorShader->SetUniform1i("texture1", 0);
    }

    void TestBlendingSorted::OnUpdate(float delteTime) {

    }

    void TestBlendingSorted::OnRender() {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        GLCall(processInput(m_window));

        // transparent vegetation locations
    // --------------------------------
        std::vector<glm::vec3> vegetation
        {
            glm::vec3(-1.5f, 0.0f, -0.48f),
            glm::vec3(1.5f, 0.0f, 0.51f),
            glm::vec3(0.0f, 0.0f, 0.7f),
            glm::vec3(-0.3f, 0.0f, -2.3f),
            glm::vec3(0.5f, 0.0f, -0.6f)
        };

        Render render;

        std::map<float, glm::vec3> sorted;
        for (unsigned int i = 0; i < vegetation.size(); i++) {
            float distance = glm::length(camera.Position - vegetation[i]);
            sorted[distance] = vegetation[i];
        }

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_ColorShader->SetUniformMat4f("view", view);
        m_ColorShader->SetUniformMat4f("projection", projection);

        //cubes
        m_ColorShader->SetUniform1i("texture1", 0);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_ColorShader->SetUniformMat4f("model", model);
        render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_ColorShader);

        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        m_ColorShader->SetUniformMat4f("model", model);
        render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_ColorShader);

        //plane
        m_ColorShader->SetUniform1i("texture1", 1);
        m_ColorShader->SetUniformMat4f("model", glm::mat4(1.0f));
        render.DrawElements(*m_VAO1, *m_IndexBuffer1, *m_ColorShader);

        //grass 
        m_ColorShader->SetUniform1i("texture1", 2);
        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend();++it) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, it->second);
            m_ColorShader->SetUniformMat4f("model", model);
            render.DrawArrays(*m_VAO2, *m_ColorShader);
        }

    }

    void TestBlendingSorted::OnImGuiRender() {

    }
}
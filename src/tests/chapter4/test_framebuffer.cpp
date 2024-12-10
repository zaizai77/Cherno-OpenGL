#include "test_framebuffer.h"

#include "Render.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"
#include "FrameBuffer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

/// <summary>
/// 这个代码有点问题，但是我还没有解决。不开启渲染缓冲对象时可以
/// 正常将立方体绘制，但是开启之后立方体变成了黑色
/// </summary>

namespace test {
    TestFrameBuffer::TestFrameBuffer() {
        m_FramebufferShader = std::make_unique<Shader>("res/shaders/chapter4/framebuffer.shader");
        m_FramebufferScreenShader = std::make_unique<Shader>("res/shaders/chapter4/framebuffer_screen.shader");
    }
    TestFrameBuffer::~TestFrameBuffer() {}

    void TestFrameBuffer::OnStart(GLFWwindow* window) {
        GLCall(m_window = window);
        glEnable(GL_DEPTH_TEST);
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

        float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        GLCall(m_Texture0 = std::make_unique<Texture>("res/textures/container.jpg"));
        GLCall(m_Texture1 = std::make_unique<Texture>("res/textures/metal.png"));

        GLCall(m_Texture0->Bind(0));
        //GLCall(m_Texture1->Bind(1));

        //cube VAO
        GLCall(m_VAO0 = std::make_unique<VertexArray>());

        GLCall(m_VertexBuffer0 = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices)));
        VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(3);
        cubeLayout.Push<float>(2);
        m_VAO0->AddBuffer(*m_VertexBuffer0, cubeLayout);
        m_IndexBuffer0 = std::make_unique<IndexBuffer>(cubeIndices, 36);

        //plane VAO
        m_VAO1 = std::make_unique<VertexArray>();
        m_VertexBuffer1 = std::make_unique<VertexBuffer>(planeVertices, sizeof(planeVertices));
        VertexBufferLayout planeLayout;
        planeLayout.Push<float>(3);
        planeLayout.Push<float>(2);
        m_VAO1->AddBuffer(*m_VertexBuffer1, planeLayout);
        m_IndexBuffer1 = std::make_unique<IndexBuffer>(planeIndices, 6);

        //Screen Quad VAO
        m_ScreenQuad_VAO = std::make_unique<VertexArray>();
        m_ScreenQuad_VertexBuffer = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
        VertexBufferLayout screenQuadLayout;
        screenQuadLayout.Push<float>(2);
        screenQuadLayout.Push<float>(2);
        GLCall(m_ScreenQuad_VAO->AddBuffer(*m_ScreenQuad_VertexBuffer, screenQuadLayout));

        m_FramebufferShader->Bind();
        GLCall(m_FramebufferShader->SetUniform1i("texture1", 0));

        m_FramebufferScreenShader->Bind();
        GLCall(m_FramebufferScreenShader->SetUniform1i("screenTexture", 0));

        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        ///create a color attachment texture

        GLCall(glGenTextures(1, &textureColorbuffer));
        GLCall(glBindTexture(GL_TEXTURE_2D, textureColorbuffer));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0));
        
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

        GLCall(glGenRenderbuffers(1, &rbo));
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, rbo));
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT)); // use a single renderbuffer object for both a depth AND stencil buffer.
        GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo)); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

        GLCall(m_FrameBuffer->BufferComplete());

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        // framebuffer configuration
    // -------------------------
}

    void TestFrameBuffer::OnUpdate(float delteTime) {

    }

    void TestFrameBuffer::OnRender() {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        GLCall(processInput(m_window));

        Render render;

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        m_FramebufferShader->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        GLCall(m_FramebufferShader->SetUniformMat4f("view", view));
        GLCall(m_FramebufferShader->SetUniformMat4f("projection", projection));

        //cubes
        m_VAO0->Bind();
        GLCall(m_FramebufferShader->SetUniform1i("texture1", 0));
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        GLCall(m_FramebufferShader->SetUniformMat4f("model", model));
        GLCall(render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_FramebufferShader));

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        GLCall(m_FramebufferShader->SetUniformMat4f("model", model));
        GLCall(render.DrawElements(*m_VAO0, *m_IndexBuffer0, *m_FramebufferShader));

        //plane
        m_VAO1->Bind();
        GLCall(m_Texture1->Bind(0));
        GLCall(m_FramebufferShader->SetUniform1i("texture1", 0));
        GLCall(m_FramebufferShader->SetUniformMat4f("model", glm::mat4(1.0f)));
        GLCall(render.DrawElements(*m_VAO1, *m_IndexBuffer1, *m_FramebufferShader));
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
    
        m_FramebufferScreenShader->Bind();
        m_ScreenQuad_VAO->Bind();
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        GLCall(render.DrawArrays(*m_ScreenQuad_VAO, *m_FramebufferScreenShader));
    
    }

    void TestFrameBuffer::OnImGuiRender() {

    }
}
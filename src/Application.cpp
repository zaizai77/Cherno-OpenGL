#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Render.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestTextureBlend.h"
#include "tests/TestTenRotateCube.h"
#include "tests/TestLightColor.h"
#include "tests/TestLightCasterDirectional.h"
#include "tests/TestLightCasterPoint.h"
#include "tests/TestLightCasterFlashLight.h"
#include "tests/chapter3/model_loading.h"
#include "tests/chapter4/test_depth_testing.h"
#include "tests/chapter4/test_stencil_testing.h"

using namespace test;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //指定opengl版本，3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //指定opengl次要版本 0.3  即3.3 
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //兼容版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心版本

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {  //should after MakeContextCurrent 
        std::cout << "Error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    Render render;

    /* Setup Dear ImGui context */
    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    test::Test* currentTest = nullptr;
    test::TestMenu* TestMenu = new test::TestMenu(currentTest);
    currentTest = TestMenu;

    //TestMenu->RegisterTest<test::TestClearColor>("Clear Color");
    //TestMenu->RegisterTest<test::TestTexture2D>("TestTexture2D");
    //TestMenu->RegisterTest<test::TestTextureBlend>("TestTextureBlend");
    //TestMenu->RegisterTest<test::TestTenRotateCube>("TestTenRotateCube");
    //TestMenu->RegisterTest<test::TestLightColor>("TestLightColor");
    //TestMenu->RegisterTest<test::TestLightCasterDirectional>("TestLightCasterDirectional");
    //TestMenu->RegisterTest<test::TestLightCasterPoint>("TestLightCasterPoint");
    TestMenu->RegisterTest<test::TestLightCasterFlashLight>("TestLightCasterFlashLight");
    TestMenu->RegisterTest<test::ModelLoading>("ModelLoading");
    TestMenu->RegisterTest<test::TestDepthTesting>("TestDepthTesting");
    TestMenu->RegisterTest<test::TestStencilTesting>("TestStencilTesting");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        render.Clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest) {
            currentTest->OnStart(window);
            currentTest->OnUpdate(0.0f);
            //currentTest->ProcessInput(window);
            currentTest->OnRender();
            ImGui::Begin("Test");
            // 后退
            if (currentTest != TestMenu && ImGui::Button("<-")) {
                delete currentTest;
                currentTest = TestMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        //函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
        //它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwSwapBuffers(window);

        //函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、
        //更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
        glfwPollEvents();
    }

    if (currentTest != TestMenu) {
        delete currentTest;
        currentTest = nullptr;
    }
    delete TestMenu;
    TestMenu = nullptr;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
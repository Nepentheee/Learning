#include <iostream>
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>
#include "DebugLog.h"
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Shader.h"
#include "stb_image.h"
#include "Renderer.h"

#include "Tests/TestClearColor.h"
#include "Tests/TestTexture2D.h"
#include "Tests/TestBatchRender.h"
#include "Tests/TestCameram.h"
#include "Tests/TestLight.h"

#include "Application.h"

using namespace std;

float deltaTime = 0.0f;
test::Test* currentTest = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	//cout << width << "," << height << endl;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (currentTest != nullptr)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			currentTest->OnProcessInput(0, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			currentTest->OnProcessInput(1, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			currentTest->OnProcessInput(2, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			currentTest->OnProcessInput(3, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (currentTest != nullptr)
	{
		currentTest->OnMouseMove(xpos, ypos);
	}
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (currentTest != nullptr)
	{
		currentTest->OnScrollMove(xOffset, yOffset);
	}
}

void ChangeInterger(int &a)
{
	a = 2;
}

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//OpenGL 3.3 Core_Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//cout << "Version: " << glfwGetVersionString() << endl;

	Log("Version: " + string(glfwGetVersionString()));

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(960, 640, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Fail to initialize GLAD" << endl;
		return -1;
	}

	// äÖÈ¾´°¿Ú´óÐ¡
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	// Enable DepthTest
	glEnable(GL_DEPTH_TEST);

	// Enable Blend
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Ã¿Ö¡äÖÈ¾
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Êó±êÊäÈë
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, mouse_callback);
	
	// ¹öÂÖÊäÈë
	glfwSetScrollCallback(window, scroll_callback);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	Log("Maximum nr of vertex attributes supported: " + to_string(nrAttributes));

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");

	Renderer renderer;

	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
	testMenu->RegisterTest<test::TestBatchRender>("Batch Render");
	testMenu->RegisterTest<test::TestCamera>("Test Camera");
	testMenu->RegisterTest<test::TestLight>("Test Light");

	// Wire frame Mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FIll);

	float lastTime = 0.0f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currTime = glfwGetTime();
		deltaTime = currTime - lastTime;
		lastTime = currTime;

		processInput(window);

		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (currentTest != testMenu)
	{
		delete testMenu;
	}
	delete currentTest;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

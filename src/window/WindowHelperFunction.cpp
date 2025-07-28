#include "window/WindowHelperFunction.h"
#include "window/window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int src::InitWndLib(void)
{
	int result = glfwInit();

	if (result == GLFW_FALSE)
	{
		std::printf("Failed to initialize window library.\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}

void src::SetContext(GLFWwindow* window, class Window* windowClass)
{
	glfwSetWindowUserPointer(window, windowClass);
	glfwMakeContextCurrent(window);
}

GLFWwindow* src::CreateWindow(const char* name, math::Vector2<int> size)
{
	// Create window
	GLFWwindow* windowPtr = glfwCreateWindow(size[0], size[1], name, NULL, NULL);

	// Set callbacks
	glfwSetWindowSizeCallback(windowPtr, SizeCallback);

	return windowPtr;
}

void src::CloseWindow(GLFWwindow* windowPtr)
{
	if (windowPtr)
		glfwSetWindowShouldClose(windowPtr, true);
}

bool src::ShouldWndClose(GLFWwindow* windowPtr)
{
	if (windowPtr)
		return glfwWindowShouldClose(windowPtr);

	/*
	*	Passed invalid window ptr therefore unable to know
	*	if window should stay open therefore we close the window
	*/
	return true;
}

void src::UpdateWindow(GLFWwindow* windowPtr)
{
	glfwSwapBuffers(windowPtr);
	glfwPollEvents();
}

void src::SizeCallback(GLFWwindow* windowPtr, int width, int height)
{
	Window* wndClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowPtr));

	if (wndClass)
	{
		// Update window transform
		float aspectRatio = (height == 0) ? static_cast<float>(width / height) : width;

		wndClass->SetSize(width, height);
		wndClass->SetAspectRatio(aspectRatio);

		glViewport(0, 0, width, height);
	}
}

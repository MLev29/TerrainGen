#include "input/InputCallbacks.h"
#include "input/InputHandler.h"

#include <iostream>

void src::callback::KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	(void) window;

	src::InputHandler::KeyboardCallback(key, scanCode, action, mods);
}

void src::callback::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	(void) window;

	src::InputHandler::MouseButtonCallback(button, action, mods);
}

void src::callback::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	(void) window;

	src::InputHandler::MouseScrollCallback(xOffset, yOffset);
}

void src::callback::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	(void) window;

	src::InputHandler::CursorPosCallback(xPos, yPos);
}

void src::callback::SetCursorMode(int mode)
{
	glfwSetInputMode(glfwGetCurrentContext(), CURSOR, mode);
}

int src::callback::InitCallbacks(void)
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (window)
	{
		glfwSetKeyCallback(window, KeyboardCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetScrollCallback(window, MouseScrollCallback);
	}
	else
	{
		std::printf("Failed to set input callbacks\n");
		return -1;
	}

	return 0;
}

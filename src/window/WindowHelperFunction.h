#pragma once

#include "LibMath/vector/Vector2.h"

#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 5

struct GLFWwindow;

namespace src
{
	int InitWndLib(void);
	void SetContext(GLFWwindow* window, class Window* windowClass);
	GLFWwindow* CreateWindow(const char* name, math::Vector2<int> size);
	void CloseWindow(GLFWwindow* windowPtr);
	bool ShouldWndClose(GLFWwindow* windowPtr);
	void UpdateWindow(GLFWwindow* windowPtr);


	void SizeCallback(GLFWwindow* windowPtr, int width, int height);
}
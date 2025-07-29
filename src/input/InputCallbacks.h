#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace src::callback
{
    void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);

    void SetCursorMode(int mode);

    int InitCallbacks(void);
}
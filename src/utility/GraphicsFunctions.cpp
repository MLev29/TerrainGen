#include "utility/GraphicsFunctions.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int src::InitGraphicsApi(void)
{
	int result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	if (!result)
	{
		std::printf("Failed to initialize glad.\n");
		return -1;
	}

	return 0;
}

void src::Clear(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

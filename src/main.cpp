//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>

#include "window/window.h"

int main(void)
{
	src::Window window("TerrainGen", 960, 540);

	window.Init();

	while (!window.ShouldWindowClose())
	{
		window.Update();
	}

	return 0;
}

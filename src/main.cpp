#include "window/window.h"
#include "input/InputHandler.h"

int main(void)
{
	src::Window window("TerrainGen", 960, 540);
	window.Init();


	src::InputHandler::StartUp();


	while (!window.ShouldWindowClose())
	{
		window.Update();

		if (src::InputHandler::IsInputDown(KEY_E))
			printf("e pressed\n");

		src::InputHandler::UpdateKeyState();
	}

	src::InputHandler::ShutDown();

	return 0;
}

#include "window/window.h"
#include "input/InputHandler.h"
#include "utility/GraphicsFunctions.h"
#include "utility/Timer.h"
#include "camera/Camera.h"
#include "resource/ResourceManager.h"
#include "resource/shader/Shader.h"
#include "utility/Buffer.h"
#include "rendering/mesh/Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define FILL 0

int main()
{
	src::Window window("TerrainGen", 960, 540);
	window.Init();
	glEnable(GL_DEPTH_TEST);
	src::InputHandler::StartUp();

	src::Camera camera({0.0f, 0.0f, 0.0f}, 15.0f);

	auto gridShader = src::ResourceManager::LoadShader(
		"TerrainShader", 
		"shaders/Terrain.vert", 
		"shaders/Terrain.frag",
		"shaders/Terrain.tesc",
		"shaders/Terrain.tese"
	);
	src::Grid grid({0.0f, 0.0f}, {100.0f, 100.0f}, 100);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#if FILL == 0
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif



	glPatchParameteri(GL_PATCH_VERTICES, 4);
	//glDisable(GL_CULL_FACE);
	src::InputHandler::SetCursorMode(src::ECursorMode::MODE_DISABLED);

	while (!window.ShouldWindowClose())
	{
		// Update systems
		src::g_time.Update();
		src::InputHandler::UpdateKeyState();

		// Camera update
		camera.CameraInput(window, src::g_time.GetDeltaTime());
		camera.MouseMotion(src::InputHandler::GetCursorPosition<float>(), src::g_time.GetDeltaTime());
		auto viewMatrix = camera.GetViewMatrix();
		auto projMatrix = camera.GetPerspectiveMatrix(0.01f, 250.0f, 60.0f, window.GetAspectRatio());
		
		src::Clear();

		// Set uniform values
		gridShader->Use();
		gridShader->Set("view", &viewMatrix);
		gridShader->Set("projection", &projMatrix);

		gridShader->Set("genCount", 6);

		// draw grid
		grid.Update();

		window.Update();
	}

	src::ResourceManager::ShutDown();
	
	return 0;
}

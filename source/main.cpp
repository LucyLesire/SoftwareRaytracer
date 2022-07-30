//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"
#include "SceneManager.h"


void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}



int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - Lesire Lucy 2DAE14",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize objects

	auto& sceneManager = Elite::SceneManager::GetInstance();
	auto& lightManager = Elite::LightManager::GetInstance();

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;
	int currentScene = 0;
	while (isLooping)
	{
		//--------- Render ---------
		pRenderer->Render();

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}

		sceneManager.Update(pTimer->GetTotal());

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_X])
		{
			if (currentScene == 1)
			{
				currentScene = 0;
				pRenderer->SetCurrentScene(currentScene);
			}
			else if (currentScene == 0)
			{
				currentScene = 1;
				pRenderer->SetCurrentScene(currentScene);
			}
		}
		
		isLooping = sceneManager.GetScene()[currentScene]->UpdateKeys();

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;

	ShutDown(pWindow);
	return 0;
}
/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

#include <cstdint>
#include "Scene.h"
#include "ECamera.h"
#include "BaseMaterial.h"

struct SDL_Window;
struct SDL_Surface;

class Camera;
class BaseMaterial;

namespace Elite
{
	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer() = default;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Render();
		bool SaveBackbufferToImage() const;

		void SetCurrentScene(int i) { m_pCurrentScene = m_pScenes[i]; }

		void InitalizeScenes();

	private:
		SDL_Window* m_pWindow = nullptr;
		SDL_Surface* m_pFrontBuffer = nullptr;
		SDL_Surface* m_pBackBuffer = nullptr;
		uint32_t* m_pBackBufferPixels = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene = nullptr;

		Elite::FMatrix4 m_LookAtMatrix{};
		float m_Fov{};
		float m_AspectRatio{};

		int m_CurrentScene{};

		Elite::FVector3 GetDirection(const uint32_t& c, const uint32_t& r);
	};
}

#endif
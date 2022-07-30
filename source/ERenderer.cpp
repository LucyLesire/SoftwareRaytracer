//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"
#include "ERGBColor.h"
#include "SceneManager.h"
#include "MaterialManager.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include "LambertMaterial.h"
#include "PBRMaterial.h"
#include "PointLight.h"
#include "BaseLight.h"
#include "DirectionalLight.h"
#include "Parser.h"

Elite::Renderer::Renderer(SDL_Window * pWindow)
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
	
	SceneManager::GetInstance().AddScene(new Scene());
	m_pScenes.push_back(SceneManager::GetInstance().GetScene()[0]);

	SceneManager::GetInstance().AddScene(new Scene());
	m_pScenes.push_back(SceneManager::GetInstance().GetScene()[1]);

	InitalizeScenes();

	m_CurrentScene = 0;
	m_pCurrentScene = m_pScenes[m_CurrentScene];

	m_AspectRatio = float(m_Width) / float(m_Height);
}

void Elite::Renderer::InitalizeScenes()
{
	LambertMaterial* lambertGreyBlue = new LambertMaterial(1.0f, Elite::RGBColor{ 0.49f, 0.57f, 0.57f });
	LambertMaterial* lambertWhite = new LambertMaterial(1.0f, Elite::RGBColor{ 1.f, 1.f, 1.f });
	LambertMaterial* lambertRedPurple = new LambertMaterial(1.0f, Elite::RGBColor{ 0.8f, 0.f, 0.4f });

	PBRMaterial* pbrRoughMetal = new PBRMaterial(Elite::RGBColor{ 0.f,0.f,0.f }, 1.f, 1.f, true, Elite::RGBColor(0.972f, 0.96f, 0.915f));
	PBRMaterial* pbrMediumMetal = new PBRMaterial(Elite::RGBColor{ 0.f,0.f,0.f }, 1.f, 0.6f, true, Elite::RGBColor(0.972f, 0.96f, 0.915f));
	PBRMaterial* pbrSmoothMetal = new PBRMaterial(Elite::RGBColor{ 0.f,0.f,0.f }, 1.f, 0.1f, true, Elite::RGBColor(0.972f, 0.96f, 0.915f));
	PBRMaterial* pbrRoughPlastic = new PBRMaterial(Elite::RGBColor{ 0.75f, 0.75f, 0.75f }, 1.f, 1.f, false);
	PBRMaterial* pbrMediumPlastic = new PBRMaterial(Elite::RGBColor{ 0.75f, 0.75f, 0.75f }, 1.f, 0.4f, false);
	PBRMaterial* pbrSmoothPlastic = new PBRMaterial(Elite::RGBColor{ 0.75f, 0.75f, 0.75f }, 1.f, 0.1f, false);

	MaterialManager::GetInstance().AddMaterial(lambertGreyBlue);
	MaterialManager::GetInstance().AddMaterial(lambertWhite);
	MaterialManager::GetInstance().AddMaterial(lambertRedPurple);
	MaterialManager::GetInstance().AddMaterial(pbrSmoothMetal);
	MaterialManager::GetInstance().AddMaterial(pbrMediumMetal);
	MaterialManager::GetInstance().AddMaterial(pbrRoughMetal);
	MaterialManager::GetInstance().AddMaterial(pbrSmoothPlastic);
	MaterialManager::GetInstance().AddMaterial(pbrMediumPlastic);
	MaterialManager::GetInstance().AddMaterial(pbrRoughPlastic);

	m_pScenes[0]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(0.f, 0.f, 0.f), Elite::FVector3(0.f, 1.f, 0)));
	m_pScenes[0]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(0.f, 0.f, -10.f), Elite::FVector3(0.f, 0.f, 1.0f)));
	m_pScenes[0]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(0.f, 10.f, 0.f), Elite::FVector3(0.f, -1.f, 0.f)));
	m_pScenes[0]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(5.f, 0, 0.f), Elite::FVector3(-1.f, 0.f, 0.f)));
	m_pScenes[0]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(-5.f, 0, 0.f), Elite::FVector3(1.f, 0.f, 0.f)));

	m_pScenes[0]->AddObject(new Sphere(pbrSmoothMetal, Elite::FPoint3(-1.75f, 1.f, 0.f), 0.75f));
	m_pScenes[0]->AddObject(new Sphere(pbrMediumMetal, Elite::FPoint3(0, 1.f, 0.f), 0.75f));
	m_pScenes[0]->AddObject(new Sphere(pbrRoughMetal, Elite::FPoint3(1.75f, 1.f, 0.f), 0.75f));
	m_pScenes[0]->AddObject(new Sphere(pbrSmoothPlastic, Elite::FPoint3(-1.75f, 3.f, 0.f), 0.75f));
	m_pScenes[0]->AddObject(new Sphere(pbrMediumPlastic, Elite::FPoint3(0, 3.f, 0.f), 0.75f));
	m_pScenes[0]->AddObject(new Sphere(pbrRoughPlastic, Elite::FPoint3(1.75f, 3.f, 0.f), 0.75f));

	m_pScenes[0]->AddObject(new Triangle(lambertWhite, Elite::FMatrix4({ 1,0,0,0 }, { 0,1,0,0 }, { 0,0,1,0 }, { -1.75f, 4.5f, 0.f, 1 }), CullMode::BackFace));
	m_pScenes[0]->AddObject(new Triangle(lambertWhite, Elite::FMatrix4({ 1,0,0,0 }, { 0,1,0,0 }, { 0,0,1,0 }, { 0.f, 4.5f, 0.f, 1 }), CullMode::FrontFace));
	m_pScenes[0]->AddObject(new Triangle(lambertWhite, Elite::FMatrix4({ 1,0,0,0 }, { 0,1,0,0 }, { 0,0,1,0 }, { 1.75f, 4.5f, 0.f, 1 }), CullMode::NoCull));

	LightManager::GetInstance().AddLight(new PointLight(Elite::FPoint3{ 0, 5.f, -5.f }, Elite::RGBColor{ 1.f, 0.61f, 0.45f }, 50.f));
	LightManager::GetInstance().AddLight(new PointLight(Elite::FPoint3{ -2.5f, 5.f, 5.f }, Elite::RGBColor{ 1.f, 0.8f, 0.45f }, 70.f));
	LightManager::GetInstance().AddLight(new PointLight(Elite::FPoint3{ 2.5f, 2.5f, 5.f }, Elite::RGBColor{ 0.34f, 0.47f, 0.68f }, 50.f));

	m_pScenes[0]->AddLights(LightManager::GetInstance().GetLights());

	Parser parser{};
	std::vector<FPoint3> vertexBuffer{};
	std::vector<IPoint3> indexBuffer{};
	parser.ParseObject(vertexBuffer, indexBuffer, "lowpoly_bunny.obj");

	m_pScenes[1]->AddObject(new TriangleMesh(vertexBuffer, indexBuffer, FMatrix4({ 1,0,0,0 }, { 0,1,0,0 }, { 0,0,1,0 }, { 0,0,0,1 }), lambertRedPurple));
	m_pScenes[1]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(0.f, 0.f, 0.f), Elite::FVector3(0.f, 1.f, 0)));
	m_pScenes[1]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(0.f, 0.f, -10.f), Elite::FVector3(0.f, 0.f, 1.0f)));
	m_pScenes[1]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(0.f, 10.f, 0.f), Elite::FVector3(0.f, -1.f, 0.f)));
	m_pScenes[1]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(5.f, 0, 0.f), Elite::FVector3(-1.f, 0.f, 0.f)));
	m_pScenes[1]->AddObject(new Plane(lambertGreyBlue, Elite::FPoint3(-5.f, 0, 0.f), Elite::FVector3(1.f, 0.f, 0.f)));

	m_pScenes[1]->AddLights(LightManager::GetInstance().GetLights());
}

void Elite::Renderer::Render()
{
	SDL_LockSurface(m_pBackBuffer);

	Ray ray{ Elite::FPoint3{0,0,0}, Elite::FVector3{0,0,-1} };

	HitRecord hitRecord{};

	m_LookAtMatrix = m_pCurrentScene->GetCamera()->LookAt();
	m_Fov = m_pCurrentScene->GetCamera()->GetFov();

	ray.m_Origin = Elite::FPoint3(m_LookAtMatrix[3].xyz);

	int o{};

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			ray.m_Direction = GetDirection(c, r);

			if (m_pCurrentScene->Hit(ray, hitRecord, o))
			{
				Elite::RGBColor finalColour{};

				finalColour = m_pCurrentScene->CalculateLights(hitRecord, ray, o);

				finalColour.MaxToOne();

				m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
					static_cast<uint8_t>(finalColour.r * 255),
					static_cast<uint8_t>(finalColour.g * 255),
					static_cast<uint8_t>(finalColour.b * 255));
			}
			else
			{

				m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
					static_cast<uint8_t>(0),
					static_cast<uint8_t>(0),
					static_cast<uint8_t>(0));
			}
		}
	}
	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}


Elite::FVector3 Elite::Renderer::GetDirection(const uint32_t& c, const uint32_t& r)
{
	const float xss = ((2 * (c + 0.5f) / m_Width) - 1) * m_AspectRatio * m_Fov;
	const float yss = -(1 - (2 * (r + 0.5f) / m_Height)) * m_Fov;

	Elite::FPoint4 pixelWorldPos = { xss,yss, 1.f, 0.f };

	pixelWorldPos = m_LookAtMatrix * pixelWorldPos;

	return (Elite::FPoint3(m_LookAtMatrix[3].xyz) - pixelWorldPos.xyz);
}

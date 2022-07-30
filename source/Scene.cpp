#include "Scene.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include "ECamera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "LambertMaterial.h"
#include "PhongMaterial.h"
#include "PBRMaterial.h"
#include "MaterialManager.h"
#include <SDL.h>
#include "BaseMaterial.h"
#include "Parser.h"
Elite::Scene::Scene()
{
	Initialize();
}

void Elite::Scene::Initialize()
{
	m_pCamera = new Elite::Camera();
}

Elite::Scene::~Scene()
{
	for (std::vector<Object*>::iterator it{ m_pObjects.begin() }; it != m_pObjects.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}
	m_pObjects.clear();

	delete m_pCamera;
	m_pCamera = nullptr;
}

void Elite::Scene::AddObject(Object* obj)
{
	m_pObjects.push_back(obj);
}

void Elite::Scene::AddLights(std::vector<BaseLight*> pLights)
{
	m_pLights = pLights;
}

bool Elite::Scene::Hit(const Ray& ray, HitRecord& hitRecord, int& o)
{
	hitRecord.light = false;
	hitRecord.tValue = FLT_MAX;

	for (int i{}; i < m_pObjects.size(); i++)
	{
		if (m_pObjects[i]->Hit(ray, hitRecord))
			o = i;
	}

	if (hitRecord.tValue != FLT_MAX)
	{
		return true;
	}

	return false;
}

std::vector<Elite::Object*> Elite::Scene::GetObjects()
{
	return m_pObjects;
}

void Elite::Scene::Update(float dT)
{
	m_pCamera->Update();
	for (int i{}; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->Update(dT);
	}
}

bool Elite::Scene::NoShadows() const
{
	return m_NoShadow;
}

bool Elite::Scene::NoMaterials() const
{
	return m_NoMaterial;
}

bool Elite::Scene::OnlyMaterials() const
{
	return m_OnlyMaterial;
}

bool Elite::Scene::UpdateKeys()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return false;
			break;
			/* Look for a keypress */
		case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch (event.key.keysym.sym) {
			case SDLK_q:
				m_NoShadow = !m_NoShadow;
				break;
			case SDLK_e:
				if (!m_NoMaterial && !m_OnlyMaterial)
				{
					m_OnlyMaterial = true;
				}
				else if (m_OnlyMaterial)
				{
					m_NoMaterial = true;
					m_OnlyMaterial = false;
				}
				else if (m_NoMaterial)
				{
					m_NoMaterial = false;
				}
				break;
			default:
				break;
			}
		}
	}
	return true;
}

Elite::RGBColor Elite::Scene::CalculateLights(HitRecord& hitRecord, const Ray& ray, int& o)
{
	Ray rayLight{};
	rayLight.m_TMin = 0.01f;
	rayLight.m_Origin = hitRecord.m_HitPoint;

	HitRecord hitRecordLight{};
	RGBColor finalColour{};

	int p{};

	for (int i{}; i < m_pLights.size(); i++)
	{
		Elite::FVector3 lightDirection = m_pLights[i]->GetDirection(hitRecord.m_HitPoint);
		rayLight.m_TMax = Magnitude(lightDirection);
		lightDirection = Elite::GetNormalized(lightDirection);
		rayLight.m_Direction = lightDirection;

		if (!HitLight(rayLight, hitRecordLight) || m_NoShadow)
		{
			const float observedArea = Elite::Dot((hitRecord.m_Normal), lightDirection);

			if (observedArea > 0.f)
			{
				const Elite::RGBColor radiance = m_pLights[i]->GetRadiance(hitRecord.m_HitPoint);
				if (m_NoMaterial)
				{
					finalColour += radiance * observedArea;
				}
				else if (m_OnlyMaterial)
				{
					finalColour += m_pObjects[o]->GetMaterial()->Shade(hitRecord, lightDirection, -ray.m_Direction) * observedArea;
				}
				else
				{
					finalColour += radiance * m_pObjects[o]->GetMaterial()->Shade(hitRecord, lightDirection, -ray.m_Direction) * observedArea;
				}
			}
		}
	}

	return finalColour;
}

Elite::Camera* Elite::Scene::GetCamera() const
{
	return m_pCamera;
}


bool Elite::Scene::HitLight(const Ray& ray, HitRecord& hitRecord)
{
	hitRecord.light = true;
	for (int i{}; i < m_pObjects.size(); i++)
	{
		if (m_pObjects[i]->Hit(ray, hitRecord))
		{
			return true;
		}
	}
	return false;
}

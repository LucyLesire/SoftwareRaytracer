#pragma once
#include "Object.h"
#include <vector>
#include "LightManager.h"

namespace Elite
{
	class Camera;
	class BaseMaterial;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void AddObject(Object* obj);
		void AddLights(std::vector<BaseLight*> pLights);
		bool Hit(const Ray& ray, HitRecord& hitRecord, int& o);

		std::vector<Object*> GetObjects();

		void Update(float dT);

		bool NoShadows() const;
		bool NoMaterials() const;
		bool OnlyMaterials() const;

		bool UpdateKeys();

		Elite::RGBColor CalculateLights(HitRecord& hitRecord, const Ray& ray, int& o);

		Camera* GetCamera() const;
	private:
		Camera* m_pCamera = nullptr;
		void Initialize();

		bool HitLight(const Ray& ray, HitRecord& hitRecord);

		std::vector<Object*> m_pObjects;
		std::vector<BaseLight*> m_pLights;
		std::vector<BaseMaterial*> m_pMaterials;

		bool m_Pressed{};
		bool m_NoMaterial{};
		bool m_OnlyMaterial{};
		bool m_NoShadow{};
	};
}





#pragma once
#include "ERGBColor.h"
#include "HitRecord.h"
#include "Object.h"
#include "BaseMaterial.h"

namespace Elite
{
	class Sphere final : public Object
	{
	public:
		Sphere(BaseMaterial* pMat, Elite::FPoint3 pos, float radius);
		virtual ~Sphere();

		bool Hit(const Ray& ray, HitRecord& hitRecord) override;
		void Update(float dT) override;

		BaseMaterial* GetMaterial() override;
	private:
		Elite::FPoint3 m_Pos;
		float m_Radius;
		BaseMaterial* m_pMat = nullptr;
	};
}




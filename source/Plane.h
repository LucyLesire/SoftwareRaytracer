#pragma once

#include "Object.h"

namespace Elite
{
	class Plane final : public Object
	{
	public:
		Plane(BaseMaterial* pMat, Elite::FPoint3 pos, Elite::FVector3 normal);
		virtual ~Plane();

		bool Hit(const Ray& ray, HitRecord& hitRecord) override;
		void Update(float dT) override;

		BaseMaterial* GetMaterial() override;
	private:
		Elite::FPoint3 m_Pos;
		Elite::FVector3 m_Normal;
		BaseMaterial* m_pMat = nullptr;
	};
}





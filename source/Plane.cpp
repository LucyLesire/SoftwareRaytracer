#include "Plane.h"
#include "BaseMaterial.h"

Elite::Plane::Plane(BaseMaterial* pMat, Elite::FPoint3 pos, Elite::FVector3 normal)
	:m_Pos{pos}
	,m_Normal{normal}
	,m_pMat{pMat}
{
}

Elite::Plane::~Plane()
{
}

bool Elite::Plane::Hit(const Ray& ray, HitRecord& hitRecord)
{
	const Elite::FVector3 vectorPlaneRay{ m_Pos - ray.m_Origin };

	const float t{ (Elite::Dot(vectorPlaneRay, m_Normal)) / (Elite::Dot(ray.m_Direction, m_Normal)) };
	if (t > ray.m_TMin && t < ray.m_TMax && t < hitRecord.tValue)
	{
		hitRecord.m_HitPoint = ray.m_Origin + (t * ray.m_Direction);
		hitRecord.tValue = t;
		hitRecord.m_Normal = GetNormalized(m_Normal);
		return true;
	}
	return false;
}

void Elite::Plane::Update(float dT)
{
}

Elite::BaseMaterial* Elite::Plane::GetMaterial()
{
	return m_pMat;
}


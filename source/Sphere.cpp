#include "Sphere.h"

Elite::Sphere::Sphere(BaseMaterial* pMat, Elite::FPoint3 pos, float radius)
	:m_Pos{pos}
	,m_Radius{radius}
	,m_pMat{pMat}
{
}

Elite::Sphere::~Sphere()
{
}

bool Elite::Sphere::Hit(const Ray& ray, HitRecord& hitRecord)
{
	const Elite::FVector3 vector{ ray.m_Origin - m_Pos };

	const float a{ Elite::Dot(ray.m_Direction, ray.m_Direction) };
	const float	b{ Elite::Dot(ray.m_Direction * 2, vector) };
	const float c{ Elite::Dot(vector, vector) - (m_Radius * m_Radius) };
	const float D{ b * b - (4 * a * c) };

	if (D < 0)
	{
		return false;
	}

	const float t{ (-b - sqrt(D)) / (2 * a) };

	if (t > ray.m_TMin && t < ray.m_TMax && t < hitRecord.tValue)
	{
		hitRecord.m_HitPoint = ray.m_Origin + t * ray.m_Direction;
		hitRecord.tValue = t;
		hitRecord.m_Normal = GetNormalized(hitRecord.m_HitPoint - m_Pos);
		return true;
	}
	return false;
}

void Elite::Sphere::Update(float dT)
{
}

Elite::BaseMaterial* Elite::Sphere::GetMaterial()
{
	return m_pMat;
}

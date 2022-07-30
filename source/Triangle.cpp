#include "Triangle.h"

Elite::Triangle::Triangle(BaseMaterial* pMat, const Elite::FMatrix4& posMatrix, const CullMode& cullMode, const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2)
	: m_TransMatrix {posMatrix}
	, m_v0{ v0 }
	, m_v1{ v1 }
	, m_v2{ v2 }
	, m_pMat{pMat}
	, m_CullMode{cullMode}
{

}

Elite::Triangle::~Triangle()
{
}

bool Elite::Triangle::Hit(const Ray& ray, HitRecord& hitRecord)
{
	const Elite::FPoint3 v0 = m_worldv0;
	const Elite::FPoint3 v1 = m_worldv1;
	const Elite::FPoint3 v2 = m_worldv2;

	const Elite::FVector3 vectorA{ v1 - v0 };
	const Elite::FVector3 vectorB{ v2 - v0 };

	const Elite::FPoint3 center{(Elite::FVector3(v0) + Elite::FVector3(v1) + Elite::FVector3(v2)) / 3.f};

	const Elite::FVector3 normal = GetNormalized( Cross(vectorA, vectorB) );

	if (m_CullMode == CullMode::BackFace)
	{
		if (Elite::Dot(normal, ray.m_Direction) >= 0)
		{
			return false;
		}
	}
	else if (m_CullMode == CullMode::FrontFace)
	{
		if (Elite::Dot(normal, ray.m_Direction) <= 0)
		{
			return false;
		}
	}
	else if (m_CullMode == CullMode::NoCull)
	{
		if (Elite::Dot(normal, ray.m_Direction) == 0)
		{
			return false;
		}
	}



	const Elite::FVector3 L = center - ray.m_Origin;
	const float t{ (Elite::Dot(L, normal)) / (Elite::Dot(ray.m_Direction, normal)) };

	if (t < ray.m_TMin || t > ray.m_TMax || t > hitRecord.tValue)
	{
		return false;
	}

	const Elite::FPoint3 p = ray.m_Origin + t * ray.m_Direction;
	Elite::FVector3 pointToSideA = p - v0;
	Elite::FVector3 pointToSideB = p - v1;
	Elite::FVector3 pointToSideC = p - v2;

	const Elite::FVector3 edgeA{ v1 - v0 };
	const Elite::FVector3 edgeB{ v2 - v1 };
	const Elite::FVector3 edgeC{ v0 - v2 };

	if (Elite::Dot(normal, Elite::Cross(edgeA, pointToSideA)) < 0)
	{
		return false;
	}

	if (Elite::Dot(normal, Elite::Cross(edgeB, pointToSideB)) < 0)
	{
		return false;
	}

	if (Elite::Dot(normal, Elite::Cross(edgeC, pointToSideC)) < 0)
	{
		return false;
	}

	hitRecord.m_HitPoint = p;
	hitRecord.tValue = t;
	hitRecord.m_Normal = normal;
	return true;
}

void Elite::Triangle::Update(float dT)
{
	auto rotationMatrix = MakeRotation(dT, { 0.f,1.f,0.f });
	m_RotationMatrix = rotationMatrix;
	m_RotationMatrix[3].w = 1.0f;

	m_worldv0 = ((m_TransMatrix * m_RotationMatrix) * Elite::FPoint4(m_v0.x, m_v0.y, m_v0.z, 1.f)).xyz;
	m_worldv1 = ((m_TransMatrix * m_RotationMatrix) * Elite::FPoint4(m_v1.x, m_v1.y, m_v1.z, 1.f)).xyz;
	m_worldv2 = ((m_TransMatrix * m_RotationMatrix) * Elite::FPoint4(m_v2.x, m_v2.y, m_v2.z, 1.f)).xyz;
}

Elite::BaseMaterial* Elite::Triangle::GetMaterial()
{
	return m_pMat;
}

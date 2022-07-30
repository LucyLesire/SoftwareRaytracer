#include "TriangleMesh.h"
#include <SDL.h>

Elite::TriangleMesh::TriangleMesh(const std::vector<FPoint3>& pVertexBuffer, const std::vector<IPoint3>& pIndexBuffer, const FMatrix4& posMatrix, BaseMaterial* pMaterial)
{
	m_VertexBuffer = pVertexBuffer;
	m_IndexBuffer = pIndexBuffer;

	m_pMat = pMaterial;
	m_PosMatrix = posMatrix;
	
	BoundingBox();
	Initiate();
}

Elite::TriangleMesh::~TriangleMesh()
{
	delete m_pSphere;
	m_pSphere = nullptr;

	for (int i{}; i < m_pTriangles.size(); i++)
	{
		delete m_pTriangles[i];
		m_pTriangles[i] = nullptr;
	}
	m_pTriangles.clear();
}

void Elite::TriangleMesh::Initiate()
{
	for (int i{}; i < m_IndexBuffer.size(); i++)
	{
		m_pTriangles.push_back(new Triangle(m_pMat, m_PosMatrix, CullMode::NoCull, m_VertexBuffer[m_IndexBuffer[i].x - 1], m_VertexBuffer[m_IndexBuffer[i].y - 1], m_VertexBuffer[m_IndexBuffer[i].z - 1]));
	}
}

bool Elite::TriangleMesh::Hit(const Ray& ray, HitRecord& hitRecord)
{
	bool hit = false;

	if (BoundingBoxIntersection(ray))
	{
		for (Triangle* t : m_pTriangles)
		{
			if (t->Hit(ray, hitRecord))
			{
				if (hitRecord.light)
					return true;
				hit = true;

			}
		}
	}

	return hit;
}

void Elite::TriangleMesh::Update(float dT)
{
	for (Triangle* t : m_pTriangles)
	{
		t->Update(dT);
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
}

Elite::BaseMaterial* Elite::TriangleMesh::GetMaterial()
{
	return m_pMat;
}

void Elite::TriangleMesh::BoundingBox()
{
	float MinX{};
	float MinY{};
	float MinZ{};
	float MaxX{};
	float MaxY{};
	float MaxZ{};
	FPoint3 sphereCenter = Elite::FPoint3(m_PosMatrix[3].xyz);

	for (FPoint3 p : m_VertexBuffer)
	{
		if (p.x > MaxX)
		{
			MaxX = p.x;
		}

		if (p.x < MinX)
		{
			MinX = p.x;
		}

		if (p.y > MaxY)
		{
			MaxY = p.y;
		}

		if (p.y < MinY)
		{
			MinY = p.y;
		}

		if (p.z > MaxZ)
		{
			MaxZ = p.z;
		}

		if (p.z < MinZ)
		{
			MinZ = p.z;
		}
	}

	sphereCenter = { (abs(MaxX) - abs(MinX)) / 2, (abs(MaxY) - abs(MinY)) / 2, (abs(MaxZ) - abs(MinZ)) / 2 };

	float radius = abs(MaxX) + abs(MinX);
	if (abs(MaxY) + abs(MinY) > radius)
		radius = abs(MaxY) + abs(MinY);
	else if (abs(MaxZ) + abs(MinZ) > radius)
		radius = abs(MaxZ) + abs(MinZ);

	m_SpherePos = sphereCenter;
	m_SphereRadius = radius;
}

bool Elite::TriangleMesh::BoundingBoxIntersection(const Ray& ray)
{
	const Elite::FVector3 vector{ ray.m_Origin - m_SpherePos };

	const float a{ Elite::Dot(ray.m_Direction, ray.m_Direction) };
	const float	b{ Elite::Dot(ray.m_Direction * 2, vector) };
	const float c{ Elite::Dot(vector, vector) - (m_SphereRadius * m_SphereRadius) };
	const float D{ b * b - (4 * a * c) };

	if (D < 0)
	{
		return false;
	}

	const float t{ (-b - sqrt(D)) / (2 * a) };

	if (t < ray.m_TMax)
	{
		return true;
	}
	return false;
}


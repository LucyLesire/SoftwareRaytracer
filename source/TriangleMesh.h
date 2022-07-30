#pragma once
#include "EMath.h"
#include <vector>
#include "Triangle.h"
#include "Sphere.h"
namespace Elite
{
	class TriangleMesh : public Object
	{
	public:
		TriangleMesh(const std::vector<FPoint3>& vertexBuffer, const std::vector<IPoint3>& indexBuffer, const FMatrix4& posMatrix, BaseMaterial* pMaterial);
		~TriangleMesh();

		void Initiate();

		bool Hit(const Ray& ray, HitRecord& hitRecord) override;

		void Update(float dT) override;

		BaseMaterial* GetMaterial() override;

	private:
		std::vector<FPoint3> m_VertexBuffer;
		std::vector<IPoint3> m_IndexBuffer;
		std::vector<Triangle*> m_pTriangles;

		BaseMaterial* m_pMat;

		FMatrix4 m_PosMatrix{};

		Sphere* m_pSphere;
		FPoint3 m_SpherePos{};
		float m_SphereRadius{};

		bool m_Bounding{};

		void BoundingBox();
		bool BoundingBoxIntersection(const Ray& ray);
	};
}



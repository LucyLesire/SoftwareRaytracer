#pragma once
#include "Object.h"
#include "ETimer.h"

namespace Elite
{
	enum class CullMode
	{
		BackFace = 0,
		FrontFace = 1,
		NoCull = 2
	};

	class Triangle final : public Object
	{
	public:
		Triangle(BaseMaterial* pMat, const Elite::FMatrix4& posMatrix, const CullMode& cullMode, const Elite::FPoint3& v0 = { -0.75f, 1.5f, 0.f }, const Elite::FPoint3& v1 = { -0.75f, 0.f, 0.f }, const Elite::FPoint3& v2 = { 0.75f, 0.f,0.f });
		~Triangle();

		bool Hit(const Ray& ray, HitRecord& hitRecord) override;

		void Update(float dT) override;

		BaseMaterial* GetMaterial() override;
	private:
		Elite::FMatrix4 m_TransMatrix{};
		Elite::FMatrix4 m_RotationMatrix{};
		Elite::FPoint3 m_v0{};
		Elite::FPoint3 m_v1{};
		Elite::FPoint3 m_v2{};

		Elite::FPoint3 m_worldv0{};
		Elite::FPoint3 m_worldv1{};
		Elite::FPoint3 m_worldv2{};

		Elite::FPoint3 m_Pos{};

		BaseMaterial* m_pMat = nullptr;

		CullMode m_CullMode{};
	};
}



#pragma once
#include "BaseMaterial.h"
namespace Elite
{
	class PBRMaterial : public BaseMaterial
	{
	public:
		PBRMaterial(Elite::RGBColor diffuseColour, float diffuseReflectance ,float roughness, bool metal, const Elite::RGBColor& reflectivity = RGBColor{0.04f, 0.04f, 0.04f});
		~PBRMaterial();

		Elite::RGBColor Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const override;

	private:
		float m_Roughness{};
		Elite::RGBColor m_AlbedoColour{};
		bool m_Metal{};
	};
}



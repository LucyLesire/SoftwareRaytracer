#pragma once
#include "BaseMaterial.h"
namespace Elite
{
	class PhongMaterial : public BaseMaterial
	{
	public:
		PhongMaterial(RGBColor color, float specularReflectance, float phongExponent);
		~PhongMaterial();

		RGBColor Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const override;

	private:
		float m_SpecularReflectance{};
		float m_PhongExponent{};
	};
}


